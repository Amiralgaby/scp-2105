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
	// (tete(rituel.objets) == NULL ) ? printf("error phrase == NULL\n") : printf("tete de liste %s\n", tete(rituel.objets));

	printf("Afficher list objets :\n");
	afficherList(rituel.objets);
	printf("Fin Afficher list objets. \n\n");

	printf("Afficher list instructions :\n");
	afficherList(rituel.instructions);
	printf("Fin Afficher list instructions.\n\n");

	puts("Free structure...\n");
	freeRituel(&rituel);
	printf("Freed structure...\n\n");
	return 0;
}
