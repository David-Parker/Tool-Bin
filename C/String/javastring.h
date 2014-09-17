#include <stdbool.h>
#include <string.h>
#ifndef JSTRING_H
#define JSTRING_H

#define ERROR -1
/* Type definitions */
typedef struct String {
	char* text;

	char (*charAt)(struct String * str,int i);
	void (*concat)(struct String * str, struct String * append);
	bool (*equals)(struct String * str, struct String * str2);
	bool (*isEmpty)(struct String * str);
	int  (*length)(struct String * str);
} String;

/* Function Prototypes */
String newString(char* text);
char charAt(String * str, int i);
void concat(String * str, String * append);
bool equals(String * str, String * str2);
bool isEmpty(String * str);
int length(String * str);
int split(String * str, char* pattern, String arr[]);

/* Utility Functions */
int countStrings(String * str, char* pattern);

#endif
