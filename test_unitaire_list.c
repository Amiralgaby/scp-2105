#include "struct.h"

int main(int argc, char const *argv[])
{
	List l;
	l = listNouv();

	l = insertion(l,"test");
	l = insertion(l,"eoiezf");
	l = insertion(l,"placeholder");
	
	afficherList(l);
	printf("il y a \"%s\" à l'index 2\n", atIndexList(l,2));
	supprimerListe(l);
	return 0;
}
