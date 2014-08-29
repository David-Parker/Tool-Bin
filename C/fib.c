#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

/* Func Protos */
double r_fib(int n);
double l_fib(List * fib, int n, long long int last_elem, int i);
double g_fib(int n, double total, double ans);
void usage();

int main(int argc, char* argv[]) {
	if(argc != 3) {
		usage();
		return -1;
	}

	char * str = argv[1]; 
	int num = atoi(argv[2]);
	clock_t t0 = clock();

	if(!strcmp("-r",str)) {
		printf("The %dth fibonacci number is: %g\n",num,r_fib(num));
	}
	else if(!strcmp("-l",str)) {
		List * list = newList();
		printf("The %dth fibonacci number is: %g\n",num,l_fib(list,num,1LL,1));
		printList(list);
	}
	else if(!strcmp("-g",str)) {
		printf("The %dth fibonacci number is: %g\n",num,g_fib(num,0,1));
	}
	else {
		usage();
		return -1;
	}

	printf("Time to complete: %f\n", ((double)clock() - (double)t0)/CLOCKS_PER_SEC);
}

/* Recursive fiboannci in O(2^n) time and O(1) space */
double r_fib(int n) {
	return n <= 1 ? n : r_fib(n-1) + r_fib(n-2);
}

/* Recursive fibonacci in O(n) time AND O(n) space */
double l_fib(List * fib, int n, long long int last_elem, int i) {
	if(n == 0) return (double)fib->tail->val;
	char name[15];
	sprintf(name,"%d",i);
	long long int lastTotal = fib->tail->val;
	createAndAdd(fib,name,last_elem + fib->tail->val);
	return l_fib(fib,n-1,lastTotal,i+1);
}

/* Recursive fibonacci in O(n) time AND O(1) space*/
double g_fib(int n, double total, double ans) {
	if(n<=0) return 0;
	else if(n==1)return ans;
	double num = (total == 0 ? 0 : 1/total);
	return g_fib(n-1,num + 1,ans*(num +1));
}

void usage() {
	printf("USAGE: fib -[r][l][g] n\n");
}


