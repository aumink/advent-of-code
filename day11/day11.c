/*
 * day11.c
 * Solves puzzle 11 of advent of code 2017
 * http://adventofcode.com/2017/day/11
 * Created on : 7 jan. 2018
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NORTH 1 // n
#define NE 2 // ne
#define NW 3 // nw
#define SOUTH 4// s
#define SE 5 // se
#define SW 6 // s

#define FILENAME "input11.txt"
#define MAXBUFFER 1024
#define SIZE 30000

typedef struct stateTableTag{
	char* key;
	int value;
} stateTableT;

const stateTableT directions[] = {
		{"n", NORTH}, {"ne", NE}, {"nw", NW}, {"s", SOUTH}, {"se", SE}, {"sw", SW}
};

int getKey(char* c);
int findNbrSteps(char* input);
char* readInput();

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();

	char *walkedDirection = readInput();

	printf("Number of steps = %d\n", findNbrSteps(walkedDirection));

}

/*
 * Solves puzzle one and two
 * Finds the shortest distant from stating point in a hexgrind
 * to the one has walked to.
 */
int findNbrSteps(char* input){
	int key = 0;

	// use canonical coordinates for the hexagons
	int x = 0;
	int y = 0;
	int z = 0;

	int maxDist = 0;
	int currDist = 0;
	printf("Child = %s\n", input);

	char* delemit = ",";
	char* direction = strtok(input,delemit);

	while(direction){

		key = getKey(direction);

			switch (key){
			case NORTH:
				y++;
				z--;
				break;
			case NE:
				x++;
				z--;
				break;
			case NW:
				x--;
				y++;
				break;
			case SOUTH:
				y--;
				z++;
				break;
			case SE:
				x++;
				y--;
				break;
			case SW:
				x--;
				z++;
				break;
			default:
				break;
			}

			direction = strtok(NULL,delemit);
			currDist = (abs(x)+abs(y)+abs(z))/2;
			maxDist = (currDist < maxDist) ? maxDist: currDist;

	}

	printf("Max dist = %d\n", maxDist);

	return (abs(x)+abs(y)+abs(z))/2;

}

/*
 * Returns witch state a direction corresponds to
 * Returns 0 if no match in the table is found
 */
int getKey(char* c){
	for(int i = 0; i < sizeof(directions)/sizeof(stateTableT); i++){
		if(strcmp(c, directions[i].key) == 0){
			return directions[i].value;
		}
	}

	return 0; // no match found
}

/*
 * Reads input and returns pointer to array
 */
char* readInput(){
	char buffer[MAXBUFFER];

	FILE *fp = fopen(FILENAME, "r");

	if(fp != NULL){
		char* input = malloc(SIZE*sizeof(char));

		while(fgets(buffer, MAXBUFFER, fp)){
			buffer[strcspn(buffer, "\n")] = 0; // delete newline
			strcat(input, buffer);

			/*input_len += strlen(buffer)+2;
			printf("Input_len = %d\n",input_len);
			input = realloc(input, input_len*sizeof(char));

			if(input == NULL){
				fprintf(stderr, "Realloc of input array failed\n");
				exit(1);
			}else{
				strcat(input, buffer);
				//oldLength = str;
			}*/
		}

		return ++input; // skip first character since use of it's junk

	}else{
		fprintf(stderr, "Couldn't open file\n");
		exit(1);

	}
	return NULL;
}
