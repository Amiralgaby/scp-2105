#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rituel.h"

#define NB_NAMES 3
#define NB_OBJ_IMP 9

/* private function prototype */
void createNomDeRituel(char** name);
void createObjetValeurImportant(List l);

/* public function */
void createRituel(Rituel* r, bool letal, char type)
{
	srand( time( NULL ) );
	r->objets = malloc(sizeof(Maillon));
	createNomDeRituel(&r->name);
	createObjetValeurImportant(r->objets);
}

void freeRituel(Rituel* r)
{
	if (r->name != NULL)
		free(r->name);
	if(r->objets != NULL)
	{
		free(r->objets->phrase);
		free(r->objets);
	}
	r->name = NULL;
	r->objets = NULL;
	printf("Freed\n");
}

/* private function */
void createNomDeRituel(char** name)
{
	const char* tabNames[NB_NAMES] = {
		"Ira constans purus",
		"Fragmentis colligeris",
		"autre"
	};
	const char* choosen = tabNames[ rand()%NB_NAMES ];
	*name = malloc(strlen(choosen)+1);
	if (*name == NULL)
	{
		printf("malloc() error\n");
		exit(-1);
	}
	strcpy(*name,choosen); // possible overflow xD
}

void createObjetValeurImportant(List l)
{
	char* tabObjetImp[NB_OBJ_IMP] = {
		"Ordinateur",
		"rubick's cube",
		"téléphone",
		"portefeuille",
		"stylo rouge",
		"stylo bleu",
		"stylo vert",
		"produit commerciale pour adolescent",
		"lit"
	};
	const char* choosen = tabObjetImp[ rand()%NB_OBJ_IMP ];
	l->phrase = malloc(strlen(choosen)+1);
	if (l->phrase == NULL)
	{
		printf("malloc() error\n");
		exit(-1);
	}
	strcpy(l->phrase,choosen);
}