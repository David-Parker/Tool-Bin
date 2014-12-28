#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int arggc, char** argv) {
	FILE * f = fopen(argv[1],"r");
	FILE * output = fopen(argv[2],"w+");

	if(f == NULL) {
		printf("Failed to open file!\n");
		return -1;
	}

	if(output == NULL) {
		printf("Failed to create new file!\n");
		return -1;
	}

	char c, lastC;
	const char space = ' ';
	int numBraces, numApost;

	while(1) {
		c = getc(f);
		if(c == EOF)
			break;

		if(lastC != '\'') {
			if (c == '(') {
				numBraces++;
			}

			else if (c == ')') {
				numBraces--;
			}

			else if (c == '\t') {
				int random = rand()%20;
				for(int i = 0; i < random; i++) {
					fputc('\t',output);
				}
			}

			else if(c == space) {
				int random = rand()%20;
				for(int i = 0; i < random; i++) {
					fputc(space,output);
				}
			}

			else if(c == '{') {
				for(int i = 0; i < 6; i++) {
					fputc('{',output);
				}
			}

			else if (c == '}') {
				for(int i = 0; i < 6; i++) {
					fputc('}',output);
				}
			}

			else if(c == ';' && numBraces == 0) {
				int random = rand()%20;
				for(int i = 0; i < random; i++) {
					//fputc(';',output);
				}
			}

		}

		lastC = c;

		fputc(c,output);
	}

	fclose(f);
	fclose(output);

	return 0;
}