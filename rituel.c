#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "rituel.h"

#define NB_NAMES 3
#define NB_OBJ_IMP 9
#define NB_OBJ 17

/* private function prototype */
void createNomDeRituel(char** name);
List createObjetValeurImportant(List l);
List createObjets(List l);
List createInstructions(List l);

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
	r->name = NULL;
	r->objets = NULL;
	printf("Freed\n");
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
	{
		printf("malloc() error\n");
		exit(-1);
	}
	strcpy(*name,choosen);
}

List createObjetValeurImportant(List l)
{
	static const char* tabObjetImp[NB_OBJ_IMP] = {
		"un Ordinateur",
		"un rubick's cube",
		"un téléphone",
		"un portefeuille",
		"un stylo rouge",
		"un stylo bleu",
		"un stylo vert",
		"un produit commercial pour adolescent",
		"un lit"
	};
	const char* choosen = tabObjetImp[ rand()%NB_OBJ_IMP ];
	char* val = malloc(strlen(choosen)+1);
	if (val == NULL)
	{
		printf("malloc() error\n");
		exit(-1);
	}
	strcpy(val,choosen);
	return insertion(l,val);
}

List createObjets(List l)
{
	static char* tabObjet[NB_OBJ] = {
		"un stylo bleu", // 1
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
		"une chaise"
	};
	char* choosen;
	char** val = malloc(sizeof(char*));
	if (val == NULL)
	{
		printf("malloc() error\n");
		exit(-1);
	}
	for (int r = (rand()&1) + 4, i = 1; i <= r; ++i)
	{
		choosen = tabObjet[ rand()%NB_OBJ ];
		if (existe(l,choosen))
		{
			--i;
			continue;
		}
		*val = malloc(strlen(choosen)+1);
		if (*val == NULL)
		{
			printf("malloc() error\n");
			exit(-1);
		}
		strcpy(*val,choosen);
		l = insertion(l,*val);
	}
	free(val);
	return l;
}

enum{SUR,SOUS,A_COTE,PLACE_SUR,PLACE_A_L_ENVERS}ACTE;

char* transformerText(char* text)
{
	if (text == NULL) return "(error)";
	char* truc;
	if (strncasecmp(text,"un",1) == 0){
		truc = malloc(strlen("le ")+strlen(text)+1);
		strcpy(truc,"le ");
		strcat(truc,text+3);
		return truc;
	}
	if (strncasecmp(text,"une",2) == 0){
		truc = malloc(strlen("la ")+strlen(text)+1);
		strcpy(truc,"le ");
		strcat(truc,text+4);
		return truc;
	}
	return text;
}

char* randomiseObjetOrContext(List objets, List context,const int objetsLong, const int contextLong)
{
	int r = rand()%(objetsLong+contextLong);

	if (r <= objetsLong)
		return atIndexList(objets,r);
	else
		return atIndexList(context,r-objetsLong);
}

List createInstructions(List l)
{
	List context, instructions = listNouv();
	
	context = listNouv();
	context = insertion(context,"un sol");
	context = insertion(context,"un coin de la salle");
	context = insertion(context,"un bureau");

	int l1 = longueur(l), l2 = longueur(context);
	printf("l1 : %d l2 : %d\n", l1, l2);
	do
	{
		char* objetUn = randomiseObjetOrContext(l,context,l1,l2);
		char* objetDeux = randomiseObjetOrContext(l,context,l1,l2);
		printf("objetUn : %s\nobjetDeux : %s\n", objetUn, objetDeux);
		char* possessifObjetUn = transformerText(objetUn);
		char* possessifObjetDeux = transformerText(objetDeux);
		printf("mettre %s sur %s\n", possessifObjetUn, possessifObjetDeux);
	}while(0);

	return instructions;
}
