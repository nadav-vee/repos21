#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "textHandler.h"

//-----------------------------------------------------------------------------
// Hermione's magic pen - A notepad demo
// -----------
//
// General : Manages an active dynamically saved string and saves it in a file
//
// Input : String, specifying the sizes of the strings
//
// Process : switch between options
//
// Output : the current string, the last save
//
//-----------------------------------------------------------------------------
// Programmer : Nadav Aviran
// ID: 212938930
// Date : 16.11.2021
//-----------------------------------------------------------------------------

void printmenu()
{
	printf("------------------------------------------------\n");
	printf("options:\n\t1: Adding to the existing\n");
	printf("\t2: Updating parts in the text\n");
	printf("\t3: Deleting text\n");
	printf("\t4: Printing current string\n");
	printf("\t5:  Writing and saving to a file\n");
	printf("\t6: Exit\n");
	printf("------------------------------------------------\n");
}

void menu()
{
	FILE* Copy;
	
	int option, flag = 0, menuReminder = 0;
	str String = (char*)malloc(sizeof(char));
	char cor;
	*String = '\0';
	printmenu();
	scanf("%d", &option);
	while (!flag) {
		menuReminder++;
		printf("______________________START______________________\n");
		switch (option)
		{
		case 0:
			printmenu();
			break;
		case 1:
			str toAdd;
			int len1;
			toAdd = getTextdyn(&len1);
			addText(len1, &String, toAdd);
			break;
		case 2:
			str toRep;
			int len2, startIndex;
			toRep = getUpdate(&startIndex, &len2);
			updateText(&String, toRep, len2, startIndex);
			break;
		case 3:
			int todel;
			todel = getLenToDel();
			delGivenLen(&String, todel);
			break;
		case 4:
			if (!strlen(String))
				printf("null\n");
			else
				puts(String);
			break;
		case 5:
			Copy = fopen("copy.txt", "wt");
			SaveString(&String, Copy);
			fclose(Copy);
			break;
		case 6:
			free(String);
			flag = 1;
			break;
		case 7:
			Copy = fopen("copy.txt", "rt");
			printFromFile(Copy);
			fclose(Copy);
			break;
		default:
			printf("invalid\nTry pressign the Enter key again\n");
			break;
		}
		printf("_______________________END_______________________\n");
		if (!flag) 
		{
			printf("please choose options 1 - 7");
			if (menuReminder > 10)
			{
				printf("choose 0 for menu");
				menuReminder = 0;
			}
			printf("\n");
			getchar();
			option = getchar() - '0';
		}
	}
}


int main()
{
	menu();
	return 0;
}