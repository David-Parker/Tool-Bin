#include <iostream>
#include <fstream>
#include <string>
#include "add.h"

int main(int argc, char* argv[]) {
	using namespace std;
	int x = 5;
	int y = 4;
	int* seg_fault = 0;
	cout << *seg_fault;
	cout << add(x,y);
}
