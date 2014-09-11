#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include <time.h>
#include <math.h>

/* Func Protos */
char * splitStrings(char str[], int index);
void permutations(char prefix[], char str[], int length);

int main() {
	char str[] = "abcdefg";
	char prefix[64] = "";
	permutations(prefix,str,strlen(str));
}

void permutations(char prefix[], char str[], int length) {

	if(length == 0) printf("%s\n", prefix);

	else {
		for(int i = 0; i < length; i++) {
			char * new_prefix = malloc(length + 1);
			char * new_str = malloc(length + 1);

			sprintf(new_prefix,"%s%c",prefix,str[i]);
			sprintf(new_str,"%s",splitStrings(str,i));
			permutations(new_prefix,new_str,length - 1);

			free(new_prefix);
			free(new_str);
		}
	}
}

char * splitStrings(char str[], int index) {
	char * newStr = malloc(strlen(str) + 1);
	int i;
	int lastIndex = 0;
	for(i = 0; i < strlen(str); i++) {
		if(i != index) {
			newStr[lastIndex] = str[i];
			lastIndex++;
		}
	}
	newStr[strlen(str) - 1] = '\0';
	return newStr;
}









