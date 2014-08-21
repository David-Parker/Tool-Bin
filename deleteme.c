#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* Func Protos */
int r_fib(int n);
void l_fib(MyList * fib, int n, long long int last_elem);

int main() {
	MyList * fib = newList();
	l_fib(fib,70,1LL);
	printf("%llu\n", fib->tail->val);
	printList(fib);
}

int r_fib(int n) {
	return n <= 1 ? n : r_fib(n-1) + r_fib(n-2);
}

void l_fib(MyList * fib, int n, long long int last_elem) {
	if(n != 0 ) {
		char name[15];
		sprintf(name,"%d",n);
		long long int lastTotal = fib->tail->val;
		createAndAdd(fib,name,last_elem + fib->tail->val);
		l_fib(fib,n-1,lastTotal);
	}
}




