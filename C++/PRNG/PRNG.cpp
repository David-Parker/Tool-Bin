#include <string.h>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include "PRNG.h"

using namespace std;
using namespace std::chrono;


int PRNG::getEntropy() {
	auto start = system_clock::now();
	char s[64];
	sprintf(s, "%lu", start);
	s[8] = '\0';
	return atoi(s);
}

PRNG::PRNG() {
	/* Create a new PRNG object */
	seed = getEntropy();
}

unsigned int PRNG::getRandInt(unsigned int max) {
	seed = ((seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1));
	return (int) seed % max;
}

