#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* mallocAndCpy(char* str)
{
	char* toReturn;
	if (str == NULL)
	{
		toReturn = malloc(30);
		strcpy(toReturn,"mallocAndCpy(): error\n");
	}
	else
	{
		toReturn = malloc(strlen(str)+1);
		strcpy(toReturn,str);
	}
	return toReturn;
}

int isMasculin(char* text)
{
	if (*text == 'u')
		if (*++text == 'n')
			if (*++text == 'e')
				return 0; // false, c'est féminin
	return 1;
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
	char* truc = malloc(strlen(text)+4);
	if (isMasculin(text)){
		isDebutParVoyelle(text) ? strcpy(truc,"l'") : strcpy(truc,"le ");
		strcat(truc,text+3);
	}
	else {
		isDebutParVoyelle(text) ? strcpy(truc,"l'") : strcpy(truc,"la ");
		strcat(truc,text+4);
	}
	return truc;
}