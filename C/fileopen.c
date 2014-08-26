#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE* fp = fopen("TEST.txt","w+");
	fprintf(fp, "Helllo\n");
	fclose(fp);
}




