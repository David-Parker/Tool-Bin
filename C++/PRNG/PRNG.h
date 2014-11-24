#ifndef PRNG_H
#define PRNG_H

/* Empty Header */
class PRNG {
private:
	unsigned long seed;
	int getEntropy();

public:
	PRNG();
	unsigned int getRandInt(unsigned int max);
};

#endif