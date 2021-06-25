#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rituel.h"

#define NB_NAMES 3

void createRituel(Rituel* r, bool letal, char type)
{
	createNomDeRituel(&r->name);
}

void freeRituel(Rituel* r)
{
	if (r->name == NULL) return;
	free(r->name);
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
	srand( time( NULL ) );
	const char* choosen = tabNames[ rand()%NB_NAMES ];
	*name = malloc(strlen(choosen)+1);
	if (*name == NULL)
	{
		printf("malloc() error\n");
		exit(-1);
	}
	strcpy(*name,choosen); // possible overflow xD
}