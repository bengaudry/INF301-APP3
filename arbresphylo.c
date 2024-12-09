#include "arbresphylo.h"
#include "arbres.h"
#include "affichage.h"
#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG true


/// FONCTIONS UTILES ///
bool est_feuille(arbre a) {
	if (a == NULL) return false;
	return a->gauche == NULL && a->droit == NULL;
}


/* ACTE I */

void analyse_arbre_rec(arbre a, int *nb_esp, int *nb_carac)
{
	if (a == NULL) return;
	if (est_feuille(a))
	{
		(*nb_esp)++;
		return;
	}

	(*nb_carac)++;
	analyse_arbre_rec(a->gauche, nb_esp, nb_carac);
	analyse_arbre_rec(a->droit, nb_esp, nb_carac);
}

void analyse_arbre(arbre racine, int *nb_esp, int *nb_carac)
{
	*nb_esp = 0;
	*nb_carac = 0;
	analyse_arbre_rec(racine, nb_esp, nb_carac);
}

/* ACTE II */

/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y
 * mettre les caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece(arbre racine, char *espece, liste_t *seq)
{
	int rg, rd;

	// Si l'arbre est vide, l'espèce n'est pas présente
	if (racine == NULL) return 1;

	// Si on est sur une feuille, on compare la valeur de la feuille avec l'espèce recherchée
	if (est_feuille(racine))
		return strcmp(racine->valeur, espece);
		
	// On recherche récursivement dans les branches gauches et droites
	rg = rechercher_espece(racine->gauche, espece, seq);
	rd = rechercher_espece(racine->droit, espece, seq);

	// Si on trouve l'espèce dans la branche "oui", on ajoute la caractéristique dans la liste
	if (rd == 0) {
		ajouter_tete(seq, racine->valeur);
		return 0;
	}

	// Si on trouve dans la branche "non", on retourne simplement que l'espèce à été trouvée
	if (rg == 0) return 0;

	return 1;
}


/* Acte III */

/* Renvoie true si la caractéristique cherchée existe dans une branche de l'arbre.
 * 
 */
bool carac_existe(arbre *a, char *carac, arbre *a_carac) {
	if ((*a) == NULL) return false;
	//if ((*a)->gauche == NULL && (*a)->droit == NULL) return false;
	if (strcmp((*a)->valeur, carac) == 0) return 1;
	return carac_existe(&(*a)->gauche, carac, a_carac) || carac_existe(&(*a)->droit, carac, a_carac);
}

/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece_rec(arbre *a, char *espece, cellule_t *cel) {
	noeud *n;

	// Arbre vide, on ajoute toutes les caractéristiques puis l'espèce
	if (*a == NULL) {
		n = nouveau_noeud();
		n->droit = NULL;
		n->gauche = NULL;

		// Séquence de carac vide, on ajoute l'espèce
		if (cel == NULL) {
			n->valeur = espece;
			*a = n;
			return 0;
		}

		n->valeur = cel->val;
		*a = n;
		return ajouter_espece_rec(&(*a)->droit, espece, cel->suivant);
	}

	if (cel == NULL) {
		if (est_feuille(*a)) return 1;
		return ajouter_espece_rec(&(*a)->gauche, espece, cel);
	}

	// La caractéristique courante existe
	if (strcmp(cel->val, (*a)->valeur) == 0) {
		return ajouter_espece_rec(&(*a)->droit, espece, cel->suivant);
	}

	if (carac_existe(&(*a)->gauche, cel->val, a)) 
		return ajouter_espece_rec(&(*a)->gauche, espece, cel);
	if (carac_existe(&(*a)->droit, cel->val, a))
		return ajouter_espece_rec(&(*a)->droit, espece, cel);
	
	// La caractéristique courante n'existe pas
	n = nouveau_noeud();
	n->droit = NULL;
	n->gauche = *a;
	n->valeur = cel->val;
	*a = n;
	return ajouter_espece_rec(&n->droit, espece, cel->suivant);
}

int ajouter_espece(arbre *a, char *espece, cellule_t *seq) {
	int r;
	char nom_fichier_dot[1500];


	strcat(nom_fichier_dot, espece);
	strcat(nom_fichier_dot, ".dot");

	r = ajouter_espece_rec(a, espece, seq);

	generer_format_dot(*a, nom_fichier_dot);
	return r;
}


typedef struct {
	bool est_fin_ligne;
	arbre *a;
} cellule_file_val;

typedef struct cellule_file_s {
	cellule_file_val* val;
	struct cellule_file_s* suivant;
} cellule_file;

typedef struct file_s {
	cellule_file* tete;
	cellule_file* queue;
	int longueur;
} file;


file* init_file(void) {
	file *file;

	file = malloc(sizeof(file));
	file->queue = NULL;
	file->tete = NULL;
	file->longueur = 0;
	return file;
}

void file_append(file* f, arbre *a) {
	cellule_file *cel;
	cellule_file_val *val;


	cel = malloc(sizeof(cellule_file));
	val = malloc(sizeof(cellule_file_val));
	val->est_fin_ligne = (a == NULL);
	val->a = a;
	cel->val = val;
	cel->suivant = NULL;

	if (f->longueur == 0 || f->tete == NULL || f->queue == NULL) {
		f->tete = cel;
		f->queue = cel;
		f->longueur = 1;
		return;
	}
	
	f->queue->suivant = cel;
	f->queue = cel;
	f->longueur = f->longueur + 1;
	return;
}

cellule_file_val* file_pop(file* f) {
	cellule_file_val* v;
	
	v = f->tete->val;
	f->longueur = f->longueur - 1;
	f->tete = f->tete->suivant;
	if (f->tete == NULL) f->queue = NULL;
	return v;
}


/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau(arbre racine, FILE *fout)
{
	file *f;
	cellule_file_val *v;
	noeud *n;

	f = init_file();
	file_append(f, &racine);
	file_append(f, NULL);

	while (f->longueur > 0) {
		v = file_pop(f);
		// Si le noeud est NULL, on termine un niveau
		if (v->est_fin_ligne) {
			fprintf(fout, "\n");
			if (f->longueur > 0) file_append(f, NULL);
			continue;
		}
		n = *v->a;
		if (n == NULL) continue;
		if (!est_feuille(n)) {
			fprintf(fout, "%s ", n ? n->valeur : "NULL");
		}

		if (n->gauche != NULL) {
			file_append(f, &n->gauche);
		}
		if (n->droit != NULL) {
			file_append(f, &n->droit);
		}
	}
}

// Acte 4

int ajouter_carac(arbre *a, char *carac, cellule_t *seq)
{
	printf("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ " >>>>>\n");
	return 0;
}
