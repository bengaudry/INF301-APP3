#include "arbres.h"
#include "file.h"
#include <stdbool.h>
#include <stdlib.h>

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
    cellule_file *ancienne_tete;
	
	v = f->tete->val;
	f->longueur = f->longueur - 1;

    ancienne_tete = f->tete;
	f->tete = f->tete->suivant;
    free(ancienne_tete);

	if (f->tete == NULL) f->queue = NULL;
    
	return v;
}
