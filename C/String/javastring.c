#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "javastring.h"

int main(int argc, char* argv[]) {
	String str = newString("madam im adam");
	//String str2 = str.substring(&str,0,5);
	str = str.reverse(&str);
	str.printString(&str);
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
	str->printString = &printString;
	str->split = &split;
	str->substring = &substring;
	str->toLowerCase = &toLowerCase;
	str->reverse = &reverse;

	return *str;
}

char charAt(String * str, int i) {
	if(i < 0 || i > (strlen(str->text) - 1)) return ERROR;

	else return str->text[i];
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

void printString(String * str) {
	printf("%s\n", str->text);
}

String * split(String * str, char* pattern) {
	int i = 0;
	char* newstr = malloc(strlen(str->text) + 1);
	strcpy(newstr,str->text);
	int numStrings = countStrings(newstr,pattern);
	free(newstr);

	String * arr = calloc(1,numStrings*sizeof(String));
	char * pch = strtok(str->text,pattern);

	while(pch != NULL) {
		String elem = newString(pch);
		arr[i] = elem;
		pch = strtok(NULL,pattern);
		i++;
	}

	return arr;
}

String concat(String * str, String * append) {
	char* newstr = calloc(1,strlen(str->text) + strlen(append->text) + 2);
	strcat(newstr,str->text);
	strcat(newstr,append->text);

	return newString(newstr);
}

String substring(String * str, int beginIndex,int endIndex) {
	if(beginIndex < 0 || beginIndex >= length(str) || endIndex < beginIndex || endIndex >= length(str)) return *str;

	char* newstr = calloc(1,length(str));

	strcpy(newstr,str->text);
	newstr[endIndex + 1] = '\0';
	newstr = newstr+beginIndex;

	return newString(newstr);
}

String toLowerCase(String * str) {
	char* newstr = calloc(1,length(str));
	int i;
	int len = length(str);

	for(i = 0; i < len; i++) {
		if(isUppercaseLetter(str->text[i])) newstr[i] = (str->text[i] - ('A' - 'a'));
		else newstr[i] = str->text[i];
	}

	newstr[len] = '\0';

	return newString(newstr);

}

String reverse(String * str) {
	char * newstr = calloc(1,length(str) + 1);
	int len = length(str);
	int i;
	int k = len - 1;

	for(i = 0; i < (len/2) + 1; i++) {
		newstr[i] = str->text[k];
		newstr[k] = str->text[i];
		k--;
	}

	newstr[len] = '\0';

	return newString(newstr);
}

/*********************** UTILITY FUNCTIONS ***********************/

int countStrings(char* str, char* pattern) {
	int count = 0;
	char* pch;

	pch = strtok(str,pattern);

	while(pch != NULL) {
		count++;
		pch = strtok(NULL,pattern);
	}

	return count;
}

bool isUppercaseLetter(char c) {
	return (c >= 'A' && c <= 'Z');
}