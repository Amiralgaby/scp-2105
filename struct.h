#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct maillon 
{
	char* phrase;
	struct maillon *suiv;
}Maillon, *List;

/* --- List --- */

List listNouv(void);
void supprimerListe(List l);
List insererEnTete(List l, char* a);
List supprimerEnTete(List l);
List insertion(List l, char* v);
int vide(List l);
void afficherList(List l);
List supprimerEnTete(List l);

#endif /* LIST */
