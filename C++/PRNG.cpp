#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

class PRNG {
public:
	PRNG() {
		/* Create a new PRNG object */
	}

	int getRandInt(int max) {
		return getRandInt(0,max);
	}

	int getRandInt(int min, int max) {
		return max;
	}

private:
	static int getEntropy() {

	}

};

int main() {
	auto start = system_clock::now();
	char s[64];
	sprintf(s, "%lu", start); sdfsd
	s[4] = '\0';
	//auto duration = duration_cast<std::chrono::milliseconds>(system_clock::now());
	//cout << start;
	printf("%s", s);
	return 0;
}