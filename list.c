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

List insererEnTete(List p,const char* x)
{
	Maillon *m;
	m = (Maillon*)malloc(sizeof(Maillon));
	if (m == NULL)
	{
		printf("Problème d'allocation\n");
		exit(1);
	}
	char* string = strdup(x);
	if (string == NULL)
	{
		printf("Problème d'allocation\n");
		exit(1);
	}
	m->phrase = string;
	m->suiv = p;
	return m;
}

List insertion(List l,const char* x)
{
	if (vide(l))
		return insererEnTete(l,x);
	l->suiv = insertion(l->suiv,x);
	return l;
}

void afficherList(List p)
{
	while(p != NULL)
	{
		printf("%s\n", p->phrase);
		p = p->suiv;
	}
}

int existe(List l,const char* v)
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

int longueur(List l)
{
	int compt = 0;
	while(!vide(l))
	{
		++compt;
		l = l->suiv;
	}
	return compt;
}

char* atIndexList(List l,const int index)
{
	for (int i = 1; i < index; ++i)
	{
		if (vide(l))
			break;
		l = l->suiv;
	}
	return tete(l);
}

void afficherElements(List l, void (*pf)(char* val))
{
	while(l != NULL)
	{
		(*pf)(l->phrase);
		l = l->suiv;
	}
}
