#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include <time.h>
#include <math.h>
#include <windows.h>

/* Func Protos */
char * strtoken(char * string, char * delim);

int main() {
	char string[512] = "Helllo,strange,.,.,.,, ., ., -------,. , ,., ,. ,.,., ,,.,,.,. .,. ,.,cruel,and.-unsual    ., .,  ,. , , ,, ,   .... , ,  ., world, ,,,,,... . . ,,., . . . . ,. ,. , ., , , !";

	char * pch = strtoken(string, ", .-");

	while(pch != NULL) {
		printf("%s\n", pch);
		pch = strtoken(NULL,", .-");
	}
	return 0;
}

char * strtoken(char * string, char * delim) {
	static char * lastToken = NULL;

	/* Set string to the last saved state when the user passes NULL */
	if(string == NULL) 
		string = lastToken;

	/* We done boys, pack your bags. */
	if(string == NULL)
		return NULL;

	/* Find every character in delim and replace every instance of those in string with a \0 */
	for(int i = 0; i < strlen(string); i++) {
		for(int j = 0; j < strlen(delim); j++) {
			if(string[i] == delim[j]) {
				string[i] = '\0';
				/* Remove extra delimeters*/
				if(!strcmp(string,"")) string = strtoken(string + 1, delim);
				/* Increment our save pointer starting at the index after the \0 */
				lastToken = strchr(string, '\0') + 1;
				return string;
			}
		}
	}

	/* No more tokens, let's get out of here */
	lastToken = NULL;
	if(!strcmp(string,"")) return NULL;
	return string;
}












