#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "rituel.h"

#define PROGRAM_VERSION "0.2.2"

void afficherRituels();

void usage()
{
	puts("Usage : COMMAND.COM [OPTIONS]");
	puts("Voici les arguments que vous pouvez passez au programme :");
	puts("\t-h, --help\t\tAfficher l'aide et quitte le programme");
	puts("\t-v, --version\t\tAfficher la version");
	puts("\t-l <bool>\t\tMettre \"false\", par défaut \"true\"");
	puts("\t-t <1 à 6>\t\tType de rituel");

	puts("Types de rituel : ");
	afficherRituels();
	printf("\n");
}

void afficherRituels()
{
printf("\
1 Réflexion sur soi\n\n\
2 Invocation\n\n\
3 Vengeance\n\n\
4 Auto Amélioration\n\n\
5 Projection\n\n\
6 Service");
}

static void printObjet(char* nameObj)
{
	static int cmp = 0;
	printf("%d %s\n", ++cmp, nameObj);
}

static void printInstruction(char* nameInst)
{
	static int cmp = 0;
	printf("%d %s\n", ++cmp, nameInst);
}

void interagirObtentionType(char* type)
{
	puts("Choisir types :");
	afficherRituels();
	printf("\n\r\nType de rituel : ");
	do
	{
		if ((*type = getchar()) == 0) printf("Une erreur est survenue\n");
	}while(*type < '1' || *type > '6');
}

void interagirObtentionLetalite(bool* letal)
{
	char c;

	printf("Letalité  (o/n) : ");
	do
	{
		if ((c = getchar()) == 0) printf("Une erreur est survenue\n");
	}while (c != 'o' && c != 'n');

	if (c == 'o')
		*letal = true;
	else
		*letal = false;
}

int main(int argc, char *argv[])
{
	char* argp;
	bool letal = false;
	char type = '0'; // indéfini
	bool flagPassLetal = false;

	// parse arguments
	for (int argn=1 ; argn < argc; ++argn)
	{
		// help
		argp = argv[argn];
		if (strcmp(argp,"-h") == 0 || strcmp(argp,"--help") == 0)
		{
			usage();
			return 0;
		}
		// version
		if (strcmp(argp,"-v") == 0 || strcmp(argp,"--version") == 0)
		{
			puts(PROGRAM_VERSION);
			return 0;
		}
		// letalité
		if (strcmp(argp,"-l") == 0)
		{
			flagPassLetal = true;
			if (argn+1 >= argc) continue;
			if (strcmp(argv[argn+1],"false") == 0)
				letal = false;
			else
				letal = true;
			if (argv[argn+1][0] != '-')
				++argn;
			continue;
		}
		// type de rituel
		if (strcmp(argp,"-t") == 0)
		{
			if (argn+1 >= argc) { usage(); return -1; }
			if (argv[argn+1][0] >= '1' && argv[argn+1][0] <= '6')
			{
				type = argv[argn+1][0];
			}
			else{
				usage();
				return -1;
			}
			++argn;
			continue;
		}
	}

#ifdef DEBUG
	printf("letal %d, type %c\n", letal, type);
#endif

	if (flagPassLetal == false)
		interagirObtentionLetalite(&letal);
	if (type == '0')
		interagirObtentionType(&type);

#ifdef DEBUG
	printf("letal %d, type %c\n", letal, type);
#endif

	Rituel rituel;
	createRituel(&rituel,letal,type);
	printf("Rituel créé. Veuillez suivre les instructions :\n\n");

	printf("Nom : %s\n\n",getName(&rituel));

	puts("Objets Requis\n");
	afficherObjets(&rituel,printObjet);
	
	puts("\nInstructions du Rituel\n");
	afficherInstructions(&rituel,printInstruction);

	freeRituel(&rituel);
	return 0;
}