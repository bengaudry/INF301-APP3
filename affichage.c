#include <stdlib.h>
#include "arbres.h"

void generer_format_dot_rec(arbre a, FILE *dest) {
    if (a == NULL) return;
    if (a->gauche != NULL) {
        fprintf(dest, "\t%s -> %s [label = \"%s\"]\n", a->valeur, a->gauche->valeur, "non");
        generer_format_dot_rec(a->gauche, dest);
    }
    if (a->droit != NULL) {
        fprintf(dest, "\t%s -> %s [label = \"%s\"]\n", a->valeur, a->droit->valeur, "oui");
        generer_format_dot_rec(a->droit, dest);
    }
    fprintf(dest, "\t%s\n", a->valeur);
    return;
}

void generer_format_dot(arbre racine, char *nom_fichier_dest) {
    FILE *dest;

    dest = fopen(nom_fichier_dest, "w");
    if (dest == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier de destination\n");
        exit (1);
    }

    fprintf(dest, "digraph arbre {\n");
    generer_format_dot_rec(racine, dest);
    fprintf(dest, "}\n");
    fclose(dest);
}
