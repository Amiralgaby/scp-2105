#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rituel.h"

#define NB_NAMES 3
#define NB_OBJ_IMP 9
#define NB_OBJ 17

/* private function prototype */
void createNomDeRituel(char** name);
List createObjetValeurImportant(List l);
List createObjets(List l);

/* public function */
void createRituel(Rituel* r, bool letal, char type)
{
	srand( time( NULL ) );
	r->objets = listNouv();
	createNomDeRituel(&r->name);
	r->objets = createObjetValeurImportant(r->objets);
	r->objets = createObjets(r->objets);
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
		"Detritus"
	};
	const char* choosen = tabNames[ rand()%NB_NAMES ];
	*name = malloc(strlen(choosen)+1);
	if (*name == NULL)
	{
		printf("malloc() error\n");
		exit(-1);
	}
	strcpy(*name,choosen);
}

List createObjetValeurImportant(List l)
{
	static const char* tabObjetImp[NB_OBJ_IMP] = {
		"un Ordinateur",
		"un rubick's cube",
		"un téléphone",
		"un portefeuille",
		"un stylo rouge",
		"un stylo bleu",
		"un stylo vert",
		"un produit commercial pour adolescent",
		"un lit"
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

List createObjets(List l)
{
	static char* tabObjet[NB_OBJ] = {
		"un stylo bleu", // 1
		"un stylo vert",
		"un stylo rouge",
		"une trousse",
		"une paire de chaussettes en boule", // 5
		"une lampe",
		"un manteau",
		"une pile",
		"un classeur",
		"une paire de crocs", // 10
		"une serviette de bain",
		"un peignoir",
		"un cartable",
		"une housse de couette",
		"une poignée de porte", // 15
		"un cadre de photo",
		"une chaise"
	};
	char* choosen;
	char** val = malloc(sizeof(char*));
	if (val == NULL)
	{
		printf("malloc() error\n");
		exit(-1);
	}
	for (int r = (rand()&1) + 4, i = 1; i <= r; ++i)
	{
		choosen = tabObjet[ rand()%NB_OBJ ];
		if (existe(l,choosen))
		{
			--i;
			continue;
		}
		*val = malloc(strlen(choosen)+1);
		if (*val == NULL)
		{
			printf("malloc() error\n");
			exit(-1);
		}
		strcpy(*val,choosen);
		l = insertion(l,*val);
	}
	free(val);
	return l;
}