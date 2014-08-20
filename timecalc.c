#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	double timeWorked = atof(argv[1])*60;
	int hours = atoi(argv[2]);
	double minutes = atof(argv[2]) - hours;
	double total = (hours*60) + minutes*100;
	//printf("Hours: %d, Mins %f,total: %f\n", hours,minutes,total);
	double timeLeft = 2400 - timeWorked;
	double out = total + timeLeft;

	int outHours = (int)(out/60)%12;
	int outMins = out - (((int)(out/60))*60);
	printf("Time Out: %d:%02dpm",outHours,outMins);
}
