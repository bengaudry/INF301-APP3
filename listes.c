#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fichier à compléter au besoin */

void init_liste_vide(liste_t *L)
{
    L = malloc(sizeof(liste_t));
}

/*
 * Supprime toutes les cellules d'une liste L, sans faire de free sur
 * L elle-même.
 */
void liberer_liste(liste_t *L)
{
    cellule_t *cel_p;

    while (L->tete != NULL) {
        cel_p = L->tete;
        L->tete = L->tete->suivant;
        free(cel_p);
    }
}


int ajouter_tete(liste_t *L, string c)
{   /* retourne 0 si OK, 1 sinon  */
    cellule_t *cel;

    if (L == NULL) return 1;

    cel = malloc(sizeof(cellule_t));
    cel->val = c;
    cel->suivant = L->tete;
    L->tete = cel;
    return 0;
}

void afficher_liste(liste_t *L) {
    cellule_t *cel;

    printf("LISTE : \n");
    cel = L->tete;
    while (cel != NULL) {
        printf("%s\n", cel->val);
        cel = cel->suivant;
    }
}

