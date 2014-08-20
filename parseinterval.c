#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char rdBuf[512] = "#n,-,3,_,2,256;";
	int ret = GetNthParameter(rdBuf, 6);
	printf("%d\n", ret);
}

int GetNthParameter(char rdBuf[], int n) {
	int val;
	int count = 0;
	char * entry = strtok(rdBuf," ,;");
	while(entry) {
		if(count < n) {
			val = atoi(entry);
			count++;
		}
		entry = strtok(NULL," ,;");
	}
	return val;
}

