/*
 * day5.c
 * http://adventofcode.com/2017/day/5
 *
 * Created on : 19 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>

#define MAXBUFFER 10

size_t readInput(int **array);
void solvePartOne(int *input, size_t nbrElements);

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();

	int *input;
	size_t nbrRead = readInput(&input);

	solvePartOne(input, nbrRead);


	free(input);
}

/*
 * Counts how many steps it takes to exit a list of type
 * [0 3 0 1 -3], where the number indicates how many steps to advance
 * for each point.
 * After one leaves a point, it's value increases with one;
 */

void solvePartOne(int *input, size_t nbrElements){

	int nbrSteps = 0;
	int index = 0;
	int prevIndex = index;

	// count nbr of steps to reach exit
	while(index < nbrElements){
		prevIndex = index;
		index += input[index];

		// change previous points value
		if(input[prevIndex] >= 3){
			input[prevIndex]--;
		}else{
			input[prevIndex]++;
		}

		nbrSteps++;
	}

	printf("It takes %d steps to reach the exit.\n", nbrSteps);

}
/*
 * Reads input from file and stores in an array.
 * The input is assumed to have one value on each line
 * Return number of values read from file
 */
size_t readInput(int **array){
	FILE *fp;
	size_t size = sizeof(int);

	fp = fopen("input5.txt", "r");

	char buffer[MAXBUFFER];

	int tal = 0;
	int index = 0;

	if(fp != NULL){
		*array =  (int*) malloc(0);

		if(*array == NULL){
			fprintf(stderr, "Malloc failed\n");
			return(-1);
		}
		while(fgets(buffer, MAXBUFFER, fp)){
			size+= sizeof(int); // increse size of array
			*array = realloc(*array, size);

			//store input in a int
			sscanf(buffer, "%d", &tal);
			(*array)[index++] = tal;
		}
	}

	return index;
}
