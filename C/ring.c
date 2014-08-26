#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
	char str[512];
	char final_str[1024] = "";
	char* new_str;
	bool skip = 0;
	int i;

	strcpy(str,argv[1]);
	new_str = strtok(str, " {|=\r\n\t");
	while(new_str != NULL) {
		if((skip = !skip)) {
			strcat(final_str,new_str);
			strcat(final_str,",");
			//printf("%s\n",new_str);
		}
		new_str = strtok(NULL, " {|=\r\n\t");
	}
	final_str[strlen(final_str)-1] = ' ';
	printf("%s\n", final_str);
}
