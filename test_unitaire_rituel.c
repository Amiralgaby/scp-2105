#include <stdio.h>
#include <string.h>
#include <time.h>
#include "rituel.h"

#define NB_NAMES 3

int main(int argc, char const *argv[])
{
	Rituel rituel;

	createRituel(&rituel,1,1);
	(rituel.name == NULL) ? printf("error name == NULL\n") : printf("%s\n", rituel.name);
	(tete(rituel.objets) == NULL ) ? printf("error phrase == NULL\n") : printf("tete de liste %s\n", tete(rituel.objets));

	puts("Free structure...");
	freeRituel(&rituel);
	return 0;
}