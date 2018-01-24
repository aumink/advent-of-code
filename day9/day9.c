/*
 * day9.c
 * Solve puzzle nine of advent of code
 * http://adventofcode.com/2017/day/9
 * Created on : 30 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT "input9.txt"
#define MAXBUFFER 20000

// Different states and corresponding values

#define VCLB 1 // {
#define VCRB 2 // }
#define VLT 3 // <
#define VGT 4 // >
#define VNOT 5 // !

typedef struct stateTableTag{
	char* key;
	int state;
} stateTableT;

const stateTableT charaters[] = {
		{"{", VCLB}, {"}", VCRB}, {"<", VLT}, {">", VGT}, {"!", VNOT}
};

void readInput(char* buffer);
void parseInput(char* c);
int findState(char* c);

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();

	char input[MAXBUFFER];

	readInput(input);

	//printf("Buffer = %s\n", input);

	parseInput(input);


}

/*
 * Reads input from file add store in a buffer
 */
void readInput(char* buffer){
	FILE *fp;

	fp = fopen(INPUT, "r");

	if(fp != NULL){
		//char buffer[MAXBUFFER];
		//printf("lenght = %d\n", sizeof(char));

		while(fgets(buffer, MAXBUFFER, fp)){
			buffer[strcspn(buffer, "\n")] = 0; // delete newline

		}
	}else{
		fprintf(stderr, "Failed to open file\n");
	}

	fclose(fp);
}

/*
 * Parsers the input and calculates the group value and number of garbage pieces
 */
void parseInput(char* c){

	int key;
	int score = 0;
	int groupValue = 0;
	int garbageState = 0; // set to 1 for true zero otherwise
	int totalGarbage = 0;

	while(*c != '\0'){
		key = findState(c);
		switch (key){
			case VCLB: // c == {
				if(garbageState == 0){ // not garbage
					groupValue++;
				}else{
					totalGarbage++; // is inside garbage
				}

				break;
			case VCRB: // c == }
				if(garbageState == 0){
					score += groupValue;
					groupValue--;
				}else{
					totalGarbage++;
				}
				break;
			case VLT: // c == <
				if(garbageState == 0){
					garbageState = 1;
				}
				else{
					totalGarbage++;
				}
				break;
			case VGT: // c == >
				if(garbageState == 1){
					garbageState = 0;
				}else{
					totalGarbage++;
				}
				break;
			case VNOT: // c == !
				c++; // ignore next character
				break;
			default: // for all other characters
				if(garbageState == 1){
					totalGarbage++;
				}
				break;
			}
		c++;
	}

	printf("Score = %d\n", score);
	printf("Total number of garbage = %d\n", totalGarbage);

}

/*
 * Returns witch state a characters belongs to
 */
int findState(char* c){

	for(int i = 0; i < sizeof(charaters)/sizeof(stateTableT); i++){
		if(strncmp(c, charaters[i].key, 1) == 0){
			return i+1; // states starting at 1
		}
	}

	return 0; // no state found
}
