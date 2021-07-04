#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rituel.h"
#include "utils.h"

/* private function prototype */
void createNomDeRituel(char** name);
List createObjetValeurImportant(List l);
List createObjets(List l);
List createInstructions(List l);

/* Getter and Print Avec Template */
char* getName(Rituel* r)
{
	return (r->name == NULL) ? "(null)" : r->name;
}

void afficherObjets(Rituel* r,void (*pf)(char* nameObj))
{
	afficherElements(r->objets,pf);
}

void afficherInstructions(Rituel* r, void (*pf)(char* nameInst))
{
	afficherElements(r->instructions,pf);
}

/* Fin des Getters et printers avec template */

/* public function */
void createRituel(Rituel* r, bool letal, char type)
{
	srand( time( NULL ) );
	r->objets = listNouv();
	r->instructions = listNouv();

	createNomDeRituel(&r->name);
	r->objets = createObjetValeurImportant(r->objets);
	r->objets = createObjets(r->objets);
	r->instructions = createInstructions(r->objets);
}

void freeRituel(Rituel* r)
{
	if (r->name != NULL)
		free(r->name);
	if(r->objets != NULL)
	{
		supprimerListe(r->objets);
	}
	if (r->instructions != NULL)
	{
		supprimerListe(r->instructions);
	}
	r->name = NULL;
	r->objets = NULL;
}

/* private function */
void createNomDeRituel(char** name)
{
	static const char* tabNames[] = {
		"Ira constans purus",
		"Fragmentis colligeris",
		"Detritus",
		"dolor sit amet",
		"Artemona Sandilius", // 5
		"Gripus Natalis",
		"Stasimus Caerellius",
		"Gulielmus Ulfila",
		"Cappadox Senilis",
		"Tycho Gluvias", // 10
		"Alcesimus Caerellius",
		"Bromia Tertius",
		"Saturio Arcadius",
		"Modestus Pullus" // 14
	};

	const size_t tabLen = sizeof(tabNames) / sizeof(tabNames[0]);

	const char* choosen = tabNames[ rand()%tabLen ];
	
	*name = malloc(strlen(choosen)+1);
	if (*name == NULL)
		errorMalloc();
	strcpy(*name,choosen);
}

List createObjetValeurImportant(List l)
{
	static const char* tabObjetImp[] = {
		"un ordinateur",
		"un rubick's cube",
		"un téléphone",
		"un portefeuille",
		"un stylo rouge", // 5
		"un stylo bleu",
		"un stylo vert",
		"un produit commercial pour adolescent",
		"un lit",
		"la première prémolaire du Sujet", // 10
		"30 ml de sang du Sujet",
		"une bande dessinée ayant marqué le sujet" // 12
	};

	const size_t tabLen = sizeof(tabObjetImp) / sizeof(tabObjetImp[0]);

	const char* choosen = tabObjetImp[ rand()%tabLen ];
	return insertion(l,choosen);
}

List createObjets(List l)
{
	static char* tabObjet[] = {
		"des stylos bleus", // 1
		"un stylo vert",
		"un stylo rouge",
		"une trousse",
		"une paire de chaussettes en boule", // 5
		"une lampe",
		"un manteau",
		"une pile",
		"un classeur",
		"une paire de crocs", // 10
		"une serviette de bain",
		"un peignoir",
		"un cartable",
		"une housse de couette",
		"une poignée de porte", // 15
		"un cadre de photo",
		"une chaise",
		"une pincée de poussière",
		"une feuille", 
		"des ciseaux", // 20
		"une brosse à dent",
		"une table",
		"une télécommande",
		"un ceintre",
		"un ventilateur", // 25
		"une horloge",
		"des écouteurs",
		"une casserole",
		"un pichet d'eau",
		"un bout de pain", // 30
		"un bol de bonbons",
		"une statue miniature",
		"un tableau" // 33
	};

	const size_t tabLen = sizeof(tabObjet) / sizeof(tabObjet[0]);

	for (int r = (rand()&1) + 4, i = 1; i <= r; ++i)
	{
		char* choosen = tabObjet[ rand()%tabLen ];
		if (existe(l,choosen))
		{
			--i;
			continue;
		}
		l = insertion(l,choosen);
	}
	return l;
}

char* randomiseObjetOrContext(List context,const int objetsLong, const int contextLong, char* objFirst, List used)
{
	int r = rand()%contextLong;
	char* choosen;

	if (strcmp(objFirst,"") == 0)
	{
		choosen = atIndexList(context,contextLong-objetsLong+r%objetsLong+1);
	}
	else
	{
		choosen = atIndexList(context,r+1);
	}

	// techniquement, si les listes sont petites (0,1) c'est une boucle infinie :(
	if (existe(used,choosen) || strcmp(choosen,objFirst) == 0) return randomiseObjetOrContext(context,objetsLong,contextLong,objFirst,used);
	return choosen;
}

enum{SUR,SOUS,A_COTE,PLACE_SUR,PLACE_SOUS,JETER,AGITER,ATTENDRE,PLACE_A_L_ENVERS}Action;

char* createInstruction(char* obj1, char* obj2)
{
	obj1 = indefiniVersDefiniArticle(obj1);
	if (obj1 == NULL)
		errorMalloc();

	obj2 = indefiniVersDefiniArticle(obj2);
	if (obj2 == NULL)
		errorMalloc();
	// on considère que obj1 et obj2 sont non nuls :)
	char* buffer = malloc(90+strlen(obj1)+strlen(obj2)); // franchement c'est bien assez pour les phrases que je fais

	if (buffer == NULL)
		errorMalloc();

	// nombre random modulo le nombre d'élément dans l'énumération
	switch(rand()%(PLACE_A_L_ENVERS+1))
	{
		case SUR:
			sprintf(buffer,"mettez %s sur %s", obj1, obj2);
			break;
		case SOUS:
			sprintf(buffer,"mettez %s sous %s", obj1, obj2);
			break;
		case A_COTE:
			sprintf(buffer,"mettez %s à côté ", obj1); // faut changer :( "de la" ou "du"
			contractAndAddArticle(&buffer,obj2);
			break;
		case PLACE_SUR:
			sprintf(buffer,"placez %s sur %s", obj1, obj2);
			break;
		case PLACE_SOUS:
			sprintf(buffer,"placez %s sous %s", obj1, obj2);
			break;
		case PLACE_A_L_ENVERS:
			sprintf(buffer,"placez %s à l'envers", obj1);
			break;
		case AGITER:
			sprintf(buffer,"agitez %s durant %d secondes", obj1, rand()%16+4);
			break;
		case JETER:
			sprintf(buffer,"jetez %s au sol", obj1);
			break;
		case ATTENDRE:
			sprintf(buffer,"attendez %d secondes", rand()%16+4);
			break;
		default:
			strcpy(buffer,"switch(action): error");
	}
	free(obj1);
	free(obj2);
	return buffer;
}

int addInListIfDoesntExist(List used, char* obj)
{
	static int nbUsed = 1;
	if (existe(used,obj))
	{
		used = insertion(used,obj);
		++nbUsed;
	}
	return nbUsed;
}

List createInstructions(List l)
{
	List context, instructions = listNouv(), used = listNouv();

	context = l;
	context = insertion(context,"un sol");
	context = insertion(context,"votre étagère à vêtement");
	context = insertion(context,"votre bureau");
	context = insertion(context,"la poubelle de votre chambre");
	
	int l1 = longueur(l), l2 = longueur(context);

	for (int x = 0, r = (rand()&3)+4; x < r; ++x)
	{
		char* objetUn = randomiseObjetOrContext(context,l1,l2,"",used);
		char* objetDeux = randomiseObjetOrContext(context,l1,l2,objetUn,used);

		char* inst = createInstruction(objetUn,objetDeux);
		instructions = insertion(instructions,inst);

		if (addInListIfDoesntExist(used,objetUn) > l1) break;
	}

	supprimerListeUntil(context,l);
	return instructions;
}
