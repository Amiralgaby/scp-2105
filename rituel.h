#ifndef RITUEL
#define RITUEL

#include <stdbool.h>
#include <stdlib.h>

typedef struct maillon{
	char* phrase;
	struct maillon* suiv;
}Maillon, *List;

typedef struct rituel
{
	char* name;
	List objets;
	List instructions;
}Rituel;

/* public functions */
void nouvRituel(Rituel* r);
void freeRituel(Rituel* r);
void createRituel(Rituel* r, bool letal, char type);
void createNomDeRituel(char** name);

#endif /* RITUEL */