#include <iostream>
#include <string>
#include "PRNG.h"

using namespace std;

int main() {
	int numTests = 10000000;
	const int range = 3;
	PRNG * p = new PRNG();

	int bins[range] = {0};

	for(int i = 0 ; i < numTests; i++) {
		bins[p->getRandInt(range)]++;
	}

	for(int i = 0; i < range; i++) {
		cout << i << ": " << ((double)bins[i] / numTests) * 100 << " %\n";
	}

	return 0;
}