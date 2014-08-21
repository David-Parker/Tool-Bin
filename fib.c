#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* Func Protos */
int r_fib(int n);
void l_fib(MyList * fib, int n, long long int last_elem, int i);
double g_fib(int n, double total, double ans);

int main() {
	// MyList * fib = newList();
	// l_fib(fib,95,1LL,1);
	// printf("%g\n", (double)fib->tail->val);
	// printList(fib);
	int num = 30;
	printf("The %dth Fib number is: %g\n",num, g_fib(num,0,1));
}

int r_fib(int n) {
	return n <= 1 ? n : r_fib(n-1) + r_fib(n-2);
}

void l_fib(MyList * fib, int n, long long int last_elem, int i) {
	if(n != 0 ) {
		char name[15];
		sprintf(name,"%d",i);
		long long int lastTotal = fib->tail->val;
		createAndAdd(fib,name,last_elem + fib->tail->val);
		l_fib(fib,n-1,lastTotal,i+1);
	}
}

double g_fib(int n, double total, double ans) {
	if(n==1)return ans;
	double num = (total == 0 ? 0 : 1/total);
	return g_fib(n-1,num + 1,ans*(num +1));
}


