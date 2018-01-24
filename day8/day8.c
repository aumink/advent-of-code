/*
 * day8.c
 * Solve day eights puzzle of advent of code 2017
 * http://adventofcode.com/2017/day/8
 * Created on : 26 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

#define MAXREG 10
#define MAXBUFFER 1024
#define INPUT "input8.txt"


typedef struct keyTableTag{
	char* key;
	int val;
} keyTableT;

static keyTableT keys[] = {
			{"<", 1}, {">", 2}, {"<=", 3}, {">=", 4}, {"==", 5}, {"!=", 6}
};

void readInRegisters(llistCDT* input);
void parseInstructions(llistCDT* reg);
int condKey(char* c);
int chkCondition(llistCDT* reg, char* regUpdate, char* regCond, char* cond, char* value);
int calcUpdateValue(char* op, char* value);

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();

	llistCDT* reg = createList();

	readInRegisters(reg);

	parseInstructions(reg);

	int max = findMaxValue(reg);

	printf("Max after all instructions is %d\n", max);

}

/*
 * Read in the registers and set their values to zero
 */
void readInRegisters(llistCDT* input){
	FILE *fp;

	fp = fopen(INPUT, "r");
	int pos = 0;

	if(fp != NULL){
		char buffer[MAXBUFFER];
		llistElementT* e = createListElem("hej", pos);

		while(fgets(buffer, sizeof(buffer)/sizeof(char), fp)){
			buffer[strcspn(buffer, "\n")] = 0; // delete newline

			char* delimit = " ";
			char* token = strtok(buffer, delimit);

			// add register to list
			changeValue(e, token, pos);
			addElement(input, *e);

		}
	}else{
		fprintf(stderr, "Failed to open file\n");
	}

	fclose(fp);
}

/*
 * Parses the instruction input and preforms the operations
 * Each line in input has the following form
 * g dec 231 if bfx > -10
 */
void parseInstructions(llistCDT* reg){
	FILE *fp;

	fp = fopen(INPUT, "r");
	int pos = 0;

	if(fp != NULL){
		char buffer[MAXBUFFER];
		int max = 0;
		int currMax;

		while(fgets(buffer, sizeof(buffer)/sizeof(char), fp)){
			buffer[strcspn(buffer, "\n")] = 0; // delete newline

			char* delimit = " ";
			char* token = strtok(buffer, delimit);

			char* regUpdate = token; // register to update
			token = strtok(NULL, delimit);

			// operation to perform
			char* operation = token;
			token = strtok(NULL, delimit);
			char* value = token;

			// condition
			token = strtok(NULL, delimit); // remove if from input
			token = strtok(NULL, delimit);
			char* regCond = token;
			token = strtok(NULL, delimit);
			char* cond = token;
			token = strtok(NULL, delimit);
			char* condValue = token;

			if(chkCondition(reg, regUpdate, regCond, cond, condValue)){
				int newValue = calcUpdateValue(operation, value);
				updateReg(reg, regUpdate, newValue);
			}

			currMax = findMaxValue(reg);

			if(currMax > max){
				max = currMax;
			}

		}

		printf("The maximum number seen during instructions is %d\n", max);
	}else{
		fprintf(stderr, "Failed to open file\n");
		//exit(1);
	}

	fclose(fp);
}

/*
 * Calculates witch value the register should be updated with
 * op "inc" = +
 * op  "dec" = -
 */
int calcUpdateValue(char* op, char* value){
	if(strcmp(op, "inc") == 0){
		return atoi(value);
	}else if(strcmp(op, "dec") == 0){
		return -1*atoi(value);
	}else{
		return 0;
	}
}

/*
 * Checks the condition and performs the update of register
 */
int chkCondition(llistCDT* reg, char* regUpdate, char* regCond, char* cond, char* value){
	int condValue = atoi(value);

	int key = condKey(cond);
	int condRegValue = getNodeValue(reg, regCond);

	switch (key) {
		case 1: //  <
			if(condRegValue < condValue){
				return 1;
			}
			break;
		case 2: // >
			if(condRegValue > condValue){
				return 1;
			}
			break;
		case 3: // <=
			if(condRegValue <= condValue){
				return 1;
			}
			break;
		case 4: // >=
			if(condRegValue >= condValue){
				return 1;
			}
			break;
		case 5: // ==
			if(condRegValue == condValue){
				return 1;
			}
			break;
		case 6: // !=
			if(condRegValue != condValue){
				return 1;
			}
			break;
		default:
			break;
	}

	return 0; // no condition was fulfilled
}

/*
 * Translate the conditions to numbers
 * {"<", ">", "<=", ">=", "==", "!="}
 * { 1,   2,    3,    4,   5,    6}
 * Returns the corresponding key
 */
int condKey(char* c){

	for(int i = 0; i < sizeof(keys)/sizeof(keyTableT); i++){
		if(strcmp(c, keys[i].key) == 0){
			return keys[i].val;
		}
	}

	return 0;
}
