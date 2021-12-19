#define _CRT_SECURE_NO_WARNINGS
#include "textHandler.h"

void allocationError()
{
	printf("ALLOCATION ERROR");
}

void addText(int size, str* string, str toAdd)
{
	int stringSize = strlen(*string);
	*string = (char*)realloc(*string, sizeof(char) * (size + 1 + stringSize));
	if (!(*string))
	{
		allocationError();
		return;
	}
	strcat(*string, toAdd);
	(*string)[stringSize + size] = '\0';
	if (strlen(toAdd))
	{
		free(toAdd);
	}
}


str getTextdyn(int* Ssize)
{
	int size;
	printf("Enter the amount of characters wanted\n");
	scanf("%d", &size);
	printf("...\n");
	str toAdd;
	toAdd = (char*)malloc(sizeof(char) * (size + 1));
	if (!toAdd)
	{
		allocationError();
		return toAdd;
	}
	getchar();
	char c;
	printf("please provide the wanted text\n");
	for (int i = 0; i < size; i++)
	{
		c = getchar();
		if (c == '\n')
		{
			toAdd[i] = '\0';
			break;
		}
		else 
		{
			toAdd[i] = c;
		}
	}
	printf("...\n");
	*Ssize = size;
	return toAdd;
}

void updateText(str* string, str toRep, int len, int start)
{
	int j = 0;
	for (int i = start; i < start + len; i++)
	{
		(*string)[i] = toRep[j++];
	}
	free(toRep);
}

str getUpdate(int *strix, int *len)
{
	int startIndx, length;
	printf("please provide starting index\n");
	scanf("%d", &startIndx);
	getchar();
	str toRep = getTextdyn(&length);
	*strix = startIndx;
	*len = length;
	return toRep;
}

void delGivenLen(str* string, int len)
{
	int slen = strlen(*string);
	int newSize = slen - len;
	str newStr = (char*)malloc(sizeof(char) * (newSize+1));
	if (!newStr)
	{
		allocationError();
		return;
	}
	for (int i = 0; i < newSize; i++)
	{
		newStr[i] = (*string)[i];
	}
	newStr[newSize] = '\0';
	free(*string);
	*string = newStr;
}

int getLenToDel()
{
	printf("please provide length to delete\n");
	int length;
	scanf("%d", &length);
	return length;
}

void SaveString(str* string, FILE* copy)
{
	fputs(*string, copy);
}

void printFromFile(FILE* file)
{
	char c;
	int spaceCount = 0, counter = 0;
	while ((c = getc(file)) != EOF)
	{
		counter++;
		if (c = ' ')
		{
			spaceCount++;
		}
		putchar(c);
		if (spaceCount > 6 || counter > 60)
		{
			printf("\n");
		}
	}
	printf("\n");
}