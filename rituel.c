#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rituel.h"
#include "utils.h"

#define NB_NAMES 3
#define NB_OBJ_IMP 10
#define NB_OBJ 21

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

inline void errorMalloc(void)
{
	printf("malloc(): error\n");
	exit(-1);
}

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
	static const char* tabNames[NB_NAMES] = {
		"Ira constans purus",
		"Fragmentis colligeris",
		"Detritus"
	};
	const char* choosen = tabNames[ rand()%NB_NAMES ];
	
	*name = malloc(strlen(choosen)+1);
	if (*name == NULL)
		errorMalloc();
	strcpy(*name,choosen);
}

List createObjetValeurImportant(List l)
{
	static const char* tabObjetImp[NB_OBJ_IMP] = {
		"un ordinateur",
		"un rubick's cube",
		"un téléphone",
		"un portefeuille",
		"un stylo rouge",
		"un stylo bleu",
		"un stylo vert",
		"un produit commercial pour adolescent",
		"un lit",
		"La première prémolaire du Sujet"
	};
	const char* choosen = tabObjetImp[ rand()%NB_OBJ_IMP ];
	
	char* val = malloc(strlen(choosen)+1);
	if (val == NULL)
		errorMalloc();

	strcpy(val,choosen);
	return insertion(l,val);
}

List createObjets(List l)
{
	static char* tabObjet[NB_OBJ] = {
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
		"30 ml de sang du Sujet",
		"une feuille", // 20
		"des ciseaux"
	};
	
	char** val = malloc(sizeof(char*));
	if (val == NULL)
		errorMalloc();

	for (int r = (rand()&1) + 4, i = 1; i <= r; ++i)
	{
		char* choosen = tabObjet[ rand()%NB_OBJ ];
		if (existe(l,choosen))
		{
			--i;
			continue;
		}
		*val = malloc(strlen(choosen)+1);
		if (*val == NULL)
			errorMalloc();

		strcpy(*val,choosen);
		l = insertion(l,*val);
	}
	free(val);
	return l;
}

char* randomiseObjetOrContext(List objets, List context,const int objetsLong, const int contextLong, char* objFirst)
{
	int r = rand()%(objetsLong+contextLong);
	char* choosen;
	if (r <= objetsLong){
		choosen = atIndexList(objets,r);
	}
	else{
		choosen = atIndexList(context,r-objetsLong);
	}
	// techniquement, si les listes sont petites (0,1) c'est une boucle infinie :(
	if (strcmp(choosen,objFirst) == 0) return randomiseObjetOrContext(objets,context,objetsLong,contextLong,objFirst);
	return choosen;
}

enum{SUR,SOUS,A_COTE,PLACE_SUR,PLACE_SOUS,PLACE_A_L_ENVERS}ACTION;

char* createAndPrintInstruction(char* obj1, char* obj2)
{
	// on considère que obj1 et obj2 sont non nuls :)
	char* buffer = malloc(90+strlen(obj1)+strlen(obj2)); // franchement c'est bien assez pour les phrases que je fais

	if (buffer == NULL)
		errorMalloc();

	// nombre random modulo le nombre d'élément dans l'énumération
	switch(rand()%(PLACE_A_L_ENVERS+1))
	{
		case SUR:
			sprintf(buffer,"mettre %s sur %s", obj1, obj2);
			break;
		case SOUS:
			sprintf(buffer,"mettre %s sous %s", obj1, obj2);
			break;
		case A_COTE:
			sprintf(buffer,"mettre %s à côté de %s", obj1, obj2); // faut changer :( "de la" ou "du"
			break;
		case PLACE_SUR:
			sprintf(buffer,"placer %s sur %s", obj1, obj2);
			break;
		case PLACE_SOUS:
			sprintf(buffer,"placer %s sous %s", obj1, obj2);
			break;
		case PLACE_A_L_ENVERS:
			sprintf(buffer,"placer %s à l'envers", obj1);
			break;
		default:
			strcpy(buffer,"switch(action): error");
	}
	return buffer;
}

List createInstructions(List l)
{
	List context, instructions = listNouv();

	context = listNouv();
	context = insertion(context,mallocAndCpy("un sol"));
	context = insertion(context,mallocAndCpy("une étagère"));
	context = insertion(context,mallocAndCpy("un bureau"));
	context = insertion(context,mallocAndCpy("une poubelle"));

	int l1 = longueur(l), l2 = longueur(context);

	for (int x = 0, r = (rand()&3)+4; x < r; ++x)
	{
		char* objetUn = randomiseObjetOrContext(l,context,l1,l2,"");
		char* objetDeux = randomiseObjetOrContext(l,context,l1,l2,objetUn);

		char* definiObjetUn = indefiniVersDefiniArticle(objetUn);
		if (definiObjetUn == NULL)
			errorMalloc();

		char* definiObjetDeux = indefiniVersDefiniArticle(objetDeux);
		if (definiObjetDeux == NULL)
			errorMalloc();

		char* inst = createAndPrintInstruction(definiObjetUn,definiObjetDeux);
		instructions = insertion(instructions,inst);

		free(definiObjetUn);
		free(definiObjetDeux);
	}

	supprimerListe(context);
	return instructions;
}
