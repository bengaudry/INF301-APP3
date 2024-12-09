#include <stdlib.h>
#include "arbres.h"
#include "affichage.h"

int main(int argc, char **argv) {
    FILE *f_arbre;
    arbre a;

    if (argc != 3) {
        fprintf(stderr, "Utilisation : %s <nom_fichier_arbre> <nom_fichier_dest>\n", argv[0]);
        return 1;
    }

    f_arbre = fopen(argv[1], "r");
    if (f_arbre == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier contenant l'arbre\n");
        exit (1);
    }

    a = lire_arbre(f_arbre);
    generer_format_dot(a, argv[2]);
    fclose(f_arbre);
    return 0;
}
