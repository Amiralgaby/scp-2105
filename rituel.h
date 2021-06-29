#ifndef RITUEL
#define RITUEL

#include <stdbool.h>
#include <stdlib.h>
#include "struct.h"

typedef struct rituel
{
	char* name;
	List objets;
	List instructions;
}Rituel;

/* public functions */
void createRituel(Rituel* r, bool letal, char type);
void freeRituel(Rituel* r);

char* getName(Rituel* r);
void afficherObjets(Rituel* r,void (*pf)(char* nameObj));
void afficherInstructions(Rituel* r, void (*pf)(char* nameInst));

#endif /* RITUEL */
