#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include <time.h>
#include <math.h>
int my_atoi(char * string);

/* Func Protos */
int main() {
	char * x = "abc23";
	printf("%d\n", my_atoi(x));
}

int my_atoi(char * string) {
	int val = 0;

	for(int i = 0; string[i] != '\0'; i++) {
		if(string[i] >= '0' && string[i] <= '9')
			val = val*10 + string[i] - '0';
	}

	return val;
}










