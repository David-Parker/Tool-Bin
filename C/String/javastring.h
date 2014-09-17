#include <stdbool.h>
#include <string.h>
#ifndef JSTRING_H
#define JSTRING_H

#define ERROR -1
#define StringArr String* 


/* Type definitions */
typedef struct String {
	char* text;

	char (*charAt)(struct String * str,int i);
	struct String (*concat)(struct String * str, struct String * append);
	bool (*equals)(struct String * str, struct String * str2);
	bool (*isEmpty)(struct String * str);
	int  (*length)(struct String * str);
	void (*printString)(struct String * str);
	struct String * (*split)(struct String * str, char* pattern);
	struct String (*substring)(struct String * str, int beginIndex,int endIndex);
	struct String (*toLowerCase)(struct String * str);
	struct String (*toUpperCase)(struct String * str);
	struct String (*reverse)(struct String * str);
	struct String (*removeSpaces)(struct String * str);
} String;

/* Function Prototypes */
String newString(char* text);
char charAt(String * str, int i);
String concat(String * str, String * append);
bool equals(String * str, String * str2);
bool isEmpty(String * str);
int length(String * str);
void printString(String * str);
String * split(String * str, char* pattern);
String substring(String * str, int beginIndex,int endIndex);
String toLowerCase(String * str);
String toUpperCase(String * str);
String reverse(String * str);
String removeSpaces(String * str);

/* Utility Functions */
int countStrings(char* str, char* pattern);
bool isUppercaseLetter(char c);
bool isLowercaseLetter(char c);

#endif
