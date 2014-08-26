#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include <time.h>

/* Func Protos */
bool isPrime(int x);


int main() {
	List * list = newList();
	createAndAdd(list,"hey",1);
	createAndAdd(list,"heyaghan",2);
	createAndAdd(list,"hsdfsdfsdfsdfsdn",3);

	printList(list);

}

bool isPrime(int x) {
	int i;
	for(i = 2; i*i <= x; i++) {
		if(x % i == 0) return false;
	}
	return true;
}






