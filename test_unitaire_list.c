#include "struct.h"

int main(int argc, char const *argv[])
{
	List l;
	l = listNouv();
	char* a = malloc(10), *b = malloc(10), *c = malloc(15);
	strcpy(a,"test");
	strcpy(b,"eoiezf");
	strcpy(c,"placeholder");
	l = insertion(l,a);
	l = insertion(l,b);
	l = insertion(l,c);
	afficherList(l);
	supprimerListe(l);
	return 0;
}