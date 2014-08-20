#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int arr[18][900];
	int i = 0;
	int j = 0;
	for(i = 0; i < 18; i++) {
		for(j = 0; j < 900; j++) {
			arr[i][j] = 7;
		}
	}
	void* newArr = calloc(1,sizeof(int)*18*900);
	memcpy(newArr,&arr,sizeof(int)*18*900);
	int test[18][900];
	memcpy(test, newArr,sizeof(int)*18*900);
	printf("Elem: %d\n", test[19][1901]);
	free(newArr);
}

    // int* arr = Data;
    // int count = 18*size;
    // for(i=0;i<count;i++) {
    //     printf("%d ",*(arr+i));
    //     if(!((i+1)%size))printf("\n");
    // }
