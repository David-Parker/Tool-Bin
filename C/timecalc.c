#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Prototypes */
void calculateTime(char* ts_time, char* fri_time);
void parseTime(char* str);
int checkState(char* in, int state);
void usage();

/* States */
#define QUIT -1
#define LOOP 0
#define HELP 1
#define TS_TIME 2
#define FRI_TIME 3

#define HOURS_IN_DAY 24
#define SECONDS_IN_HOUR 60
#define FORTY_HOURS_IN_SECONDS 2400
	
int main(int argc, char* argv[]) {
	/* Don't ask for input on stdin, use the passed in commands instead */
	if(argc == 3) {
		calculateTime(argv[1],argv[2]);
		return 1;
	}

	printf("Welcome to Intern Time Calculator, type 'help' for usage or 'quit' to exit.\n");

	char ts_time[64];
	char fri_time[64];
	char input[64];

	/* Start in the initial state */
	int state = TS_TIME;

	/* State Machine */
	while(1) {
		switch(state) {
			case TS_TIME:
				printf("\nType your total time this week from TimeSaver: ");
				scanf("%s",ts_time);
				state = checkState(ts_time,state);
				continue;
				break;
			case FRI_TIME:
				printf("Type your time in on friday (use military time): ");
				scanf("%s",fri_time);
				state = checkState(fri_time,state);
				if(state != LOOP) continue;
				calculateTime(ts_time,fri_time);
				break;
			case HELP:
				usage();
				state = TS_TIME;
				continue;
				break;
			case LOOP:
				printf("\nAgain? Type 'yes' to do another or type 'quit' to exit.\n");
				scanf("%s",input);
				state = checkState(input,state);
				break;
			case QUIT:
				exit(0);
				break;
			default:
				return -1;
		}
	}
	return 1;
}

void calculateTime(char* ts_time, char* fri_time) {
	parseTime(ts_time);
	parseTime(fri_time);
	double timeWorked = atof(ts_time)*SECONDS_IN_HOUR;
	int hours = atoi(fri_time);
	double minutes = atof(fri_time) - hours;
	double total = (hours*SECONDS_IN_HOUR) + minutes*100;
	double timeLeft = FORTY_HOURS_IN_SECONDS - timeWorked;
	double out = total + timeLeft;

	int outHours = (int)(out/SECONDS_IN_HOUR);

	if(outHours >= HOURS_IN_DAY) {
		printf("You cannot make 40hours this week!\n");
	}
	else if(outHours >= HOURS_IN_DAY/2) {
		outHours %= HOURS_IN_DAY/2;
		int outMins = out - (((int)(out/SECONDS_IN_HOUR))*SECONDS_IN_HOUR);
		printf("Time Out: %d:%02dpm\n",outHours,outMins);
	}
	else {
		int outMins = out - (((int)(out/SECONDS_IN_HOUR))*SECONDS_IN_HOUR);
		printf("Time Out: %d:%02dam\n",outHours,outMins);
	}

} 

void parseTime(char* str) {
	int i;
	char c = str[0];
	for(i = 0; c != 0; i++) {
		c = str[i];
		if(c == ':') str[i] = '.';
	}
}

int checkState(char* in, int state) {
	if(!strcmp(in,"help")) return HELP;
	else if(!strcmp(in,"quit") || !strcmp(in,"q")) return QUIT;
	else if(state == TS_TIME) return FRI_TIME;
	else if(state == LOOP) return TS_TIME;
	else if(state == FRI_TIME) return LOOP;

	/* Default Case */
	else return QUIT;
}

void usage() {
	printf("\n---------------------------------------\nUsage: timecalc [time worked] [time in]\nExample: timecalc 31.5 8:50\n---------------------------------------\n\n");
}

