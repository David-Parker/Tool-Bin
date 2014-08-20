#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int MAX = 500;
void addRecords(int data[][MAX], char str[], int index);
int main(int argc, char* argv[]) {
	char test[512] = "#d,-,19,107,1192,0,0,0,0,0,0,1192,0,0,1190,0,100,82,1,601,0,50;";
	int data[18][500];
	addRecords(data, test, 0);
}

void addRecords(int data[][MAX], char str[], int index) {
	char * entry;
	int val = 0;
	int count = 0;
	entry = strtok(str," ,;");
	while(entry != NULL) {
		if(count > 2 && count < 21) {
			val = atoi(entry);
			data[count - 3][index] = val;
			printf("[%d] val = %d\n", count - 3, data[count - 3][index]);
		}
		entry = strtok(NULL," ,;");
		count++;
	}
	printf("Final Value: %d\n", val);
}

    // for(i = 0; i < 18; i++) {
    //     printf("[%d]: ",i);
    //     for(j = 0; j < size; j++) {
    //         printf("%d ",readData[i][j]);
    //     }
    //     printf("\n");
    // }