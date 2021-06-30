#include <stdlib.h>
#include <stdio.h>
#include <string.h>

inline void errorMalloc(void)
{
	printf("malloc(): error\n");
	exit(-1);
}

char* mallocAndCpy(char* str)
{
	char* toReturn;
	if (str == NULL)
	{
		toReturn = strdup("mallocAndCpy(): error\n");
	}
	else
	{
		toReturn = strdup(str);
	}
	if (toReturn == NULL)
		errorMalloc();
	return toReturn;
}

int isMasculin(char* text)
{
	if (*text == 'u'){
		if (*++text == 'n'){
			if (*++text == 'e')
				return 0; // false, c'est féminin
			else
				return 1; // vrai, c'est masculin
		}
	}
	return -1; // indéterminé
}

inline int isPluriel(char* text)
{
	if (*text == 'd')
		if (*++text == 'e')
			if (*++text == 's')
				return 1; // vrai, c'est pluriel
	return 0; // faux, c'est singulier
}

inline int isVoyelle(char c)
{
	if (c == 'e' || c == 'a' || c == 'u' || c == 'i' || c == 'o' || c == 'y')
		return 1;
	if (c == -61) // é è ê
		return 1;
	return 0;
}

inline int isDebutParVoyelle(char* text)
{
	if ( isVoyelle( *(index(text,' ')+1) ) )
		return 1;
	return 0;
}

char* indefiniVersDefiniArticle(char* text)
{
	char* truc = malloc(strlen(text)+5);
	if (truc == NULL) errorMalloc();

	if (isPluriel(text))
	{
		strcpy(truc,"les ");
		strcat(truc,text+4);
		return truc;
	}

	int ret = isMasculin(text);
	if (ret == 1){
		isDebutParVoyelle(text) ? strcpy(truc,"l'") : strcpy(truc,"le ");
		strcat(truc,text+3);
	}
	else if (ret == 0) {
		isDebutParVoyelle(text) ? strcpy(truc,"l'") : strcpy(truc,"la ");
		strcat(truc,text+4);
	}
	else{ // ret == -1
		strcpy(truc,text);
	}
	return truc;
}