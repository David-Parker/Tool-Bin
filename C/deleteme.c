#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include <time.h>
#include <math.h>

/* Func Protos */
bool isPrime(int x);


int main() {
	double total = 2038;
	double cont = 2038;
	double cont_rate = .0;
	double rate = .08;
	double comp_num = 12; // monthly
	int t = 1;

	for(int i = 0; i < t; i++) {
		total = total + cont;
		total = total * pow((double)(1 + rate/comp_num),comp_num);
		cont *= (1 + cont_rate);
	}
	printf("Total amount after %d years with $%.02f of contributions a year: %g", t,cont,total);
}

bool isPrime(int x) {
	int i;
	for(i = 2; i*i <= x; i++) {
		if(x % i == 0) return false;
	}
	return true;
}






