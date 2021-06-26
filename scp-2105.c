#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define PROGRAM_VERSION "0.1"
#define DEBUG

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

void interagirObtentionType(char* type)
{
	char c;
	puts("Choisir types :");
	afficherRituels();
	printf("\n\r\nType de rituel : ");
	do
	{
		if (scanf("%c%*c", &c) == 0) printf("Une erreur est survenue\n");
		if (c >= '1' && c <= '6') break;
	}while(true);

	*type = c;
}

void interagirObtentionLetalite(bool* letal)
{
	char c;

	printf("Letalité  (o/n) : ");
	do
	{
		if (scanf("%c%*c",&c) == 0) printf("Une erreur est survenue\n");
		if (c == 'o' || c == 'n') break;
	}while (true); // LOL the while repeated even if c is 'o' or 'n'

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
	for (int argn=1 ; argn < argc && (argp = argv[argn])[0] == '-'; ++argn)
	{
		// help
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
			if (strcmp(argv[argn+1],"false") == 0)
				letal = false;
			else
				letal = true;
			++argn;
			continue;
		}
		// type de rituel
		if (strcmp(argp,"-t") == 0)
		{
			if (argv[argn+1][0] >= '1' && argv[argn+1][0] <= '6')
			{
				type = argv[argn+1][0];
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

	return 0;
}