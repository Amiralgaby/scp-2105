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

char* indefiniVersDefiniArticle(char* text)
{
	char* truc = malloc(strlen(text)+4);
	if (isMasculin(text)){
		strcpy(truc,"le ");
		strcat(truc,text+3);
		return truc;
	}
	else {
		strcpy(truc,"la ");
		strcat(truc,text+4);
		return truc;
	}
}