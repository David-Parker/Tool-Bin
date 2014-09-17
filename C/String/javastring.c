#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "javastring.h"

int main(int argc, char* argv[]) {
	String str = newString("Hello World!");

	String test[3];
	split(&str," ",test);

	printf("%s\n", test[1].text);
}

/************************ USER FUNCTIONS ************************/

/* Initializes a new String object */
String newString(char* text) {
	/* Create space for the inital string */
	String * str = calloc(1,sizeof(String));
	char* newstr = calloc(1,strlen(text) + 1);
	strcpy(newstr,text);
	str->text = newstr; 

	/* Add Function Pointers */
	str->charAt = &charAt;
	str->concat = &concat;
	str->equals = &equals;
	str->isEmpty = &isEmpty;
	str->length = &length;

	return *str;
}

char charAt(String * str, int i) {
	if(i < 0 || i > (strlen(str->text) - 1)) return ERROR;

	else return str->text[i];
}

void concat(String * str, String * append) {
	char* newstr = calloc(1,strlen(str->text) + strlen(append->text) + 2);
	strcat(newstr,str->text);
	strcat(newstr,append->text);

	/* Free the old string text */
	free(str->text);

	str->text = newstr;
}

bool equals(String * str, String * str2) {
	return !strcmp(str->text,str2->text);
}

bool isEmpty(String * str) {
	return !strlen(str->text);
}

int length(String * str) {
	return strlen(str->text);
}

int split(String * str, char* pattern, String arr[]) {
	int i = 0;
	//int numStrings = countStrings(str,pattern);
	//String * arr = calloc(1,numStrings*sizeof(String));
	char * pch = strtok(str->text,pattern);

	while(pch != NULL) {
		String elem = newString(pch);
		arr[i] = elem;
		pch = strtok(NULL,pattern);
		i++;
	}

	return 0;
}

/*********************** UTILITY FUNCTIONS ***********************/

int countStrings(String * str, char* pattern) {
	int count = 0;
	char* pch;

	pch = strtok(str->text,pattern);

	while(pch != NULL) {
		count++;
		pch = strtok(NULL,pattern);
	}

	return count;
}