#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Function Protos */
char* substring(char* str, int start, int end);

int main(int argc, char* argv[]) {
	char* str = "This is a real string";
	str = substring(str,2,strlen(str)-1);
	printf(str);
}

char* substring(char* str, int start, int end) {
	if(end >= strlen(str)) {
		printf("Substring Index Out of Bounds!\n");
		return str;
	} 
	char* tempBuf = malloc(strlen(str)+1);
	memcpy(tempBuf, &str[start],(end - start) + 1);
	tempBuf[(end - start) + 1] = '\0';
	return tempBuf;
}
