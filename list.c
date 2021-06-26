#include "struct.h"

/* Gabriel Theuws
List de string
*/

char* tete(List l){
	if (vide(l))
		return NULL;
	return l->phrase; 
}

int vide(List l){ return l == NULL; }

List listNouv(void){ return NULL; }

List insererEnTete(List p, char* x)
{
	Maillon *m;
	m = (Maillon*)malloc(sizeof(Maillon));
	if (m == NULL)
	{
		printf("Problème d'allocation\n");
		exit(1);
	}
	m->phrase = x;
	m->suiv = p;
	return m;
}

List insertion(List l, char* x)
{
	if (vide(l))
		return insererEnTete(l,x);
	l->suiv = insertion(l->suiv,x);
	return l;
}

List supprimerEnTete(List p)
{
	Maillon *m;
	if (p == NULL)
	{
		printf("List Vide\n");
		return p;
	}
	m = p; 
	p = p->suiv;
	free(m);
	return p;
}

void afficherList(List p)
{
	while(p != NULL)
	{
		printf("%s\n", p->phrase);
		p = p->suiv;
	}
	printf("\n");
}

int existe(List l, char* v)
{
	while (!vide(l))
	{
		if (strcmp(v,tete(l)) == 0)
			return 1;
		l = l->suiv;
	}
	return 0;
}

void supprimerListe(List l)
{
	Maillon *m;
	
	while (!vide(l))
	{
		m = l;
		char* alloue = m->phrase;
		l = l->suiv;
		free(alloue);
		free(m);
	}
}