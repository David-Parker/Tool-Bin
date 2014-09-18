#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "javastring.h"

/* String Class developed by David Parker */

/************************ USER FUNCTIONS ************************/

/* Initializes a new String object */
String newString(char* text) {
	/* Create space for the inital string */
	String * str = calloc(1,sizeof(String));
	char* newstr = calloc(1,strlen(text)+ 1);
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
	str->toUpperCase = &toUpperCase;
	str->reverse = &reverse;
	str->removeSpaces = &removeSpaces;
	str->removeCharAt = &removeCharAt;
	str->insertCharAt = &insertCharAt;

	return *str;
}

char charAt(String * str, int i) {
	if(i < 0 || i > (length(str) - 1)) return ERROR;

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
	char newstr[length(str) + 1];
	strcpy(newstr,str->text);
	int numStrings = countStrings(newstr,pattern);

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
	char newstr[length(str) + length(append) + 2];
	sprintf(newstr,"%s%s",str->text,append->text);

	return newString(newstr);
}

String substring(String * str, int beginIndex,int endIndex) {
	if(beginIndex < 0 || beginIndex >= length(str) || endIndex < beginIndex || endIndex >= length(str)) return *str;

	char * newstrptr;
	char newstr[length(str) + 1];

	strcpy(newstr,str->text);
	newstr[endIndex + 1] = '\0';
	newstrptr = newstr+beginIndex;

	return newString(newstrptr);
}

String toLowerCase(String * str) {
	int len = length(str);
	char newstr[len + 1];
	int i;

	for(i = 0; i < len; i++) {
		if(isUppercaseLetter(str->text[i])) newstr[i] = (str->text[i] - ('A' - 'a'));
		else newstr[i] = str->text[i];
	}

	newstr[len] = '\0';

	return newString(newstr);

}

String toUpperCase(String * str) {
	int i;
	int len = length(str);
	char newstr[len + 1];

	for(i = 0; i < len; i++) {
		if(isLowercaseLetter(str->text[i])) newstr[i] = (str->text[i] + ('A' - 'a'));
		else newstr[i] = str->text[i];
	}

	newstr[len] = '\0';

	return newString(newstr);
}

String reverse(String * str) {
	int len = length(str);
	char newstr[len + 1];
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

String removeSpaces(String * str) {
	int len = length(str);
	char newstr[len + 1];
	int i;
	int index = 0;

	for(i = 0; i < len; i++) {
		if(str->text[i] != ' ') {
			newstr[index] = str->text[i];
			index++;
		}
	}

	newstr[index + 1] = '\0';

	return newString(newstr);
}

String removeCharAt(String * str, int index) {
	int len = length(str);
	char newStr[len + 1];
	int i;
	int lastIndex = 0;
	for(i = 0; i < len; i++) {
		if(i != index) {
			newStr[lastIndex] = str->text[i];
			lastIndex++;
		}
	}
	newStr[len - 1] = '\0';
	return newString(newStr);
}

String insertCharAt(String * str, char c, int index) {
	int len = length(str);
	int i;
	int lastIndex = 0;
	if(index > len || len < 0) return *str;

	char newstr[len + 2];

	for(i = 0; i < len + 1; i++) {
		if(i == index) {
			newstr[i] = c;
		}
		else {
			newstr[i] = str->text[lastIndex];
			lastIndex++;
		}
	}
	
	newstr[len + 1] = '\0';

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

bool isLowercaseLetter(char c) {
	return (c >= 'a' && c <= 'z');
}
