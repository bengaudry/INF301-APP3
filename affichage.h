#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#include <stdlib.h>
#include "arbres.h"

void generer_format_dot_rec(arbre a, FILE *dest);

void generer_format_dot(arbre racine, char *nom_fichier_dest);

#endif
