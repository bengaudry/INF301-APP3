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

/* ACTE I */

void analyse_arbre_rec(arbre a, int *nb_esp, int *nb_carac)
{
	if (a == NULL) return;
	if (a->gauche == NULL && a->droit == NULL)
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
	if (racine->gauche == NULL && racine->droit == NULL)
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


/* Acte 3 */

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
		if ((*a)->gauche == NULL && (*a)->droit == NULL) return 1;
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

void afficher_seq(cellule_t *seq) {
	cellule_t *seq_init = seq;

	printf("SEQ : \n");
	while(seq != NULL) {
		printf("%s\n", seq->val);
		seq = seq->suivant;
	}
	printf("FIN SEQ\n");

	seq = seq_init;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau(arbre racine, FILE *fout)
{
	printf("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__
		   " >>>>>\n");
}

// Acte 4

int ajouter_carac(arbre *a, char *carac, cellule_t *seq)
{
	printf("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ " >>>>>\n");
	return 0;
}
