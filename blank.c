#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char test[] = "#3 1 2 3 4 5 6 7;";
	char str[20];
	int result;
	sscanf(test,"%*s %*s %*s %*s %d",&result);

	printf("Result: %d", result);
}
