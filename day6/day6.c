/*
 * day6.c
 * http://adventofcode.com/2017/day/6
 *
 * Created on : 20 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT "input6.txt"
#define MAXBUFFER 1024
#define MEMSIZE 16

typedef struct MEMSTATE{
	int nbrElements;
	int mem[MEMSIZE];
	struct MEMSTATE* next;
} MEMSTATE;

MEMSTATE* createState();


void addState(MEMSTATE** head, int* input);


int compareMemState(int* currState, MEMSTATE* prevState);


int readInput(int **input);
int solvePartOne(int* input, int length);

int findLargest(int *input, int length);




void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();

	int* input;
	int length = readInput(&input);
	printf("Cycles = %d\n", solvePartOne(input, length));

	for(int i = 0; i< length; i++){
		printf("%d ", input[i]);
		//printf("Cycle %d Input[%d]= %d\n", nbrCycles, i, input[i]);
	}

}

int solvePartOne(int* input, int length){

	MEMSTATE* prevState = createState();

	//int nbrRedist;
	int nbrCycles = 0;

	//part one
	while(compareMemState(input, prevState) == 0){
		int pos = findLargest(input, length);

		int nbrRedist = input[pos];

		addState(&prevState, input);

		input[pos] = 0; // clear current mem bloc

		// redistribute input[index] values over array
		for(int i = 0; i< nbrRedist; i++){
			pos = (pos+1)%(length); // warp around list
			input[pos]++;
		}

		nbrCycles++;
	}

	//part two
	int loopSize = 0;
	MEMSTATE* endState = createState();


	while(compareMemState(input, endState) == 0){
			int pos = findLargest(input, length);

			int nbrRedist = input[pos];

			addState(&endState, input);

			input[pos] = 0; // clear current mem bloc

			// redistribute input[index] values over array
			for(int i = 0; i< nbrRedist; i++){
				pos = (pos+1)%(length); // warp around list
				input[pos]++;
			}

			loopSize++;
	}

	printf("Loopsize %d\n", loopSize);

	return nbrCycles;
}
/*
 * Finds the position in an array with largest value
 */

int findLargest(int *input, int length){
	int index;
	int max = 0;

	for(int i = 0; i < length; i++){
		if(input[i] > max){
			max = input[i];
			index = i;
		}

	}

	return index;
}


/*
 * Reads INT values from file and stores input in an array
 * Input is seperated by tabs "\t"
 *
 */
int readInput(int **input){

	FILE *fp;

	fp = fopen(INPUT, "r");

	char buffer[MAXBUFFER];

	int index = 0;

	if(fp != NULL){
		*input = malloc(sizeof(int));
		size_t size = 0;
		char *token;
		char *delimit = "\t";

		while(fgets(buffer, MAXBUFFER, fp) != NULL){

			*input = malloc(size);

			token = strtok(buffer, delimit);

			while(token){
				size+=sizeof(int);
				realloc(*input, size);
				(*input)[index] = atoi(token);
				index++;

				token = strtok(NULL, delimit);

			}
		}
	}
	else{
		fprintf(stderr, "Failed to open file\n");
		//exit(1);
	}

	fclose(fp);

	return index;
}

/*
 * Creates a memstate linked list
 */
MEMSTATE* createState(){
	MEMSTATE* head = NULL;

	return head;
}

int compareMemState(int* currState, MEMSTATE* prevState){
	MEMSTATE* curr = prevState;
	int nrbEqualStates = 0;
	int state = 0;

	// compare all previous states with current state
	while(curr != NULL){

		// compare states
		for(int i = 0; i < MEMSIZE; i++){
			if(currState[i] == curr->mem[i])
				nrbEqualStates++;
		}

		// set true if all states are equal
		if(nrbEqualStates == MEMSIZE){
			state = 1;
			return state;
		}else{
			nrbEqualStates = 0; // reset counter;
		}

		curr = curr->next;
	}

	return state;
}

/*
 * Pushes a new memory state to the list
 */
void addState(MEMSTATE** head, int* state){
	MEMSTATE* newElement;

	newElement = malloc(sizeof(MEMSTATE));
	if(newElement == NULL){
		fprintf(stderr, "Malloc failed\n");
		exit(1);
	}

	newElement->nbrElements = MEMSIZE;

	for(int i = 0; i < MEMSIZE; i++){
		newElement->mem[i] = state[i];
	}

	newElement->next = *head;
	*head = newElement;
}
