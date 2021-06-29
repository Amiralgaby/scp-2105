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
// List insererEnTete(List l, char* a);
List insertion(List l, char* v);
int vide(List l);
char* tete(List l);
void afficherList(List l);
// List supprimerEnTete(List l);
int longueur(List l);
int existe(List l,char* string);
char* atIndexList(List l,const int index);
void afficherElements(List l, void (*pf)(char* val));

#endif /* LIST */
