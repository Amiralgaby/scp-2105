#include <stdio.h>
#include <string.h>
#include <time.h>
#include "rituel.h"

static void printObjet(char* nameObj)
{
	static int cmp = 0;
	printf("%d. %s\n", ++cmp, nameObj);
}

static void printInstruction(char* nameInst)
{
	static int cmp = 0;
	printf("%d. %s\n", ++cmp, nameInst);
}

int main(int argc, char const *argv[])
{
	Rituel rituel;

	createRituel(&rituel,1,1);

	printf("Nom du rituel : %s\n\n",getName(&rituel));

	printf("Afficher list objet 2 :\n");
	afficherObjets(&rituel,printObjet);
	printf("Fin Afficher list objet 2\n\n");

	printf("Afficher list instructions :\n");
	afficherInstructions(&rituel,printInstruction);
	printf("Fin Afficher list instructions.\n\n");

	puts("Free structure...\n");
	freeRituel(&rituel);
	printf("Freed structure...\n\n");
	return 0;
}
