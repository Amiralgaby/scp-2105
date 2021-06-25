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
	freeRituel(&rituel);
	return 0;
}