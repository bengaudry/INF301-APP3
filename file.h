#ifndef _FILE_H_
#define _FILE_H_

#include "arbres.h"
#include "file.h"
#include <stdbool.h>

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


file* init_file(void);
void file_append(file*, arbre*);
cellule_file_val* file_pop(file*);


#endif
