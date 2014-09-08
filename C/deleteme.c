#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include <time.h>
#include <math.h>

/* Func Protos */
bool isPrime(int x);
void test();

int main() {
	for(int i = 0; i < 10; i++) {
		test();
	}
	
}

bool isPrime(int x) {
	int i;
	for(i = 2; i*i <= x; i++) {
		if(x % i == 0) return false;
	}
	return true;
}

void test() {
	static int x = 5;
	x++;
	printf("%d\n", x);

}







