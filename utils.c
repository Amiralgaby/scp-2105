#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

inline const char* indexA(const char* str, char c)
{
	unsigned int index = 0;
	while(*(str+index) != '\0')
	{
		if (*(str+index) == c)
			return str+index;
		++index;
	}
	return "";
}

inline void errorMalloc(void)
{
	printf("malloc(): error\n");
	exit(-1);
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
	if ( isVoyelle( *(indexA(text,' ')+1) ) )
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

inline int whatType(char* text)
{
	if (*text == 'l')
	{
		if (*++text == 'e')
		{
			if (*++text == 's')
				return 0; // pluriel
			else
				return 1; // masculin singulier
		}
		else if (*(text+1) == 'a')
			return 2; // féminin singulier
	}
	return -1;
}

void contractAndAddArticle(char** buffer, char* obj)
{
	// de le -> du
	// de la -> de la
	// de les -> des
	// de l' -> de l'
	int ret = whatType(obj);
	if (ret == -1 || ret == 2){
		strcat(*buffer,"de ");
		strcat(*buffer,obj);
	}
	if (ret == 0){
		strcat(*buffer,"des ");
		strcat(*buffer,obj+4);
	}
	if (ret == 1){
		strcat(*buffer,"du ");
		strcat(*buffer,obj+3);
	}	
}
