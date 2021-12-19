#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* str;

//-----------------------------------------------------------------------------
// Allocation Error print
// ---------
//
// General : The function prints the messege for the memory allocation error
//
// Return Value : No return value
// Prints: Prints a messege that says "ALLOCATION ERROR"
//
//-----------------------------------------------------------------------------
void allocationError();
//-----------------------------------------------------------------------------
// Add text
// ---------
//
// General : The function adds inputed string at the end of the main string
//
// Parameters :
// size - The size of the inputed string(toAdd) (In)
// string - the main string (In)
// toAdd - The inputed string to add to the main string
//
// Return Value : void
//
//-----------------------------------------------------------------------------
void addText(int size, str* string, str toAdd);
//-----------------------------------------------------------------------------
// Get text dynamically
// ---------
//
// General : The function gets inputed size of a string,
// allocates memory with the given size,
// and gets a string from the user.
//
// Parameters :
// *Ssize - Pointer to the size of the string in order to add it to the main string.
// the paramater is a call by reference return value.
// size - temporary int to get from the user the size and to use it in the fuction
// toAdd - The string the user wants to add to the main string.
//
// Return Value : string (toAdd), int (size)
//
//-----------------------------------------------------------------------------
str getTextdyn(int *Ssize); 
// gets the variables for the last function - useful if you want to use the last funcion again

void updateText(str* string, str toRep, int len, int start);		
// updates the text given an index and the 
// string to replace the original with and it's size

str getUpdate(int* strix, int* len);	
// gets the variables for the last function - useful if you want to use the last funcion again

void delGivenLen(str* string, int len);
// delets len amount of characters from the end of the string

int getLenToDel();
// gets the variables of the last function - useful if you want to use the last funcion again

void SaveString(str* string, FILE* copy);
// saves the String in a file called copy.txt

void printFromFile(FILE* file);
// prints the last save from the file