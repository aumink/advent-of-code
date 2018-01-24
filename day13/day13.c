/*
 * day13.c
 * Solve puzzle day 13 of advent of code
 * http://adventofcode.com/2017/day/13
 * Created on : 13 jan. 2018
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXBUFFER 1024
#define SIZE 100
#define FILENAME "input13.txt"

int readInput(int* firewall, int length);
void moveScanner(int* fireWall, int* scanner, int turn);

void partTwo(int* fireWall, int* scannerState);
void partOne(int* fireWall, int* scannerState);

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();
	int fireWall[SIZE];
	for(int i = 0; i < SIZE; i++){
		fireWall[i] = 0;
	}

	readInput(fireWall, SIZE);

	int scannerState[SIZE];

	partOne(fireWall, scannerState);

	partTwo(fireWall, scannerState);

}

void partOne(int* fireWall, int* scannerState){
	int severity = 0;
	for(int i = 0; i < SIZE;){

		if(scannerState[i] == 1){
			severity += i*fireWall[i];
		}

		moveScanner(fireWall, scannerState, ++i);
	}

	printf("Severity = %d\n", severity);
}

void partTwo(int* fireWall, int* scannerState){
	int severity = 0;
	int delay = 0;
	int cought = 1;

	while(cought == 1){

		severity = 0;
		cought = 0;

		moveScanner(fireWall, scannerState, delay);

		for(int i = 0; i < SIZE;){

			if(scannerState[i] == 1){
				severity += i*fireWall[i];
				cought = 1;
				delay++;
				break;
			}
			moveScanner(fireWall, scannerState, ++i+delay);
		}
	}

	printf("Severity = %d at delay %d\n", severity, delay);


}

int readInput(int* firewall, int length){
	FILE* fp;
	int nbrElements = 0;
	fp = fopen(FILENAME, "r");

	if(fp != NULL){
		char buffer[MAXBUFFER];
		char* delimit = ": \n";

		//parse input
		while(fgets(buffer, sizeof(buffer)/sizeof(char), fp)){

			char* token = strtok(buffer, delimit);
			int layer = atoi(token);

			token = strtok(NULL, delimit);

			int deepth = atoi(token);
			firewall[layer] = deepth;

			nbrElements++;
		}
	}else{
		fprintf(stderr, "Couldn't open file\n");
		exit(1);
	}

	fclose(fp);

	return nbrElements;
}

/*
 * Update the scannerstate for first row only at turn
 */
void moveScanner(int* fireWall, int* scanner, int turn){

	for(int i = 0; i < SIZE; i++){
		if(fireWall[i] != 0 && turn%(2*(fireWall[i]-1)) == 0){
			scanner[i] = 1;
		}else{
			scanner[i] = 0;
		}
	}
}
