#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rituel.h"

#define NB_NAMES 3
#define NB_OBJ_IMP 9
#define NB_OBJ 13

/* private function prototype */
void createNomDeRituel(char** name);
List createObjetValeurImportant(List l);

/* public function */
void createRituel(Rituel* r, bool letal, char type)
{
	srand( time( NULL ) );
	r->objets = listNouv();
	createNomDeRituel(&r->name);
	r->objets = createObjetValeurImportant(r->objets);
}

void freeRituel(Rituel* r)
{
	if (r->name != NULL)
		free(r->name);
	if(r->objets != NULL)
	{
		supprimerListe(r->objets);
	}
	r->name = NULL;
	r->objets = NULL;
	printf("Freed\n");
}

/* private function */
void createNomDeRituel(char** name)
{
	static const char* tabNames[NB_NAMES] = {
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

List createObjetValeurImportant(List l)
{
	static const char* tabObjetImp[NB_OBJ_IMP] = {
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
	char* val = malloc(strlen(choosen)+1);
	if (val == NULL)
	{
		printf("malloc() error\n");
		exit(-1);
	}
	strcpy(val,choosen);
	return insertion(l,val);
}

void createObjets(List l)
{
	static const char* tabObjet[NB_OBJ] = {
		"un stylo bleu",
		"un stylo vert",
		"un stylo rouge",
		"une trousse",
		"une paire de chaussettes en boule",
		"une lampe",
		"un manteau",
		"une pile",
		"un classeur",
		"une paire de crocs",
		"une serviette de bain",
		"un peignoir",
		"un cartable"
	};
	for (int i = 1; i <= (rand()&1) + 5; ++i)
	{
		// code
	}
}