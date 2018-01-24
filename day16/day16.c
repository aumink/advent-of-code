/*
 * day16.c
 *
 *  Created on: 21 jan. 2018
 *      Author: aumink
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFERSIZE 1024
#define MAXINPUT 50000

#define SPINN 1
#define EXCHANGE 2
#define PARTNER 3
#define LENGTH 16

#define FILENAME "input16.txt"

typedef struct keyTableTag{
	char* key;
	int value;
}keyTableT;

const keyTableT stateTable[] = { {"s", SPINN}, {"x", EXCHANGE}, {"p", PARTNER}};

void spinArray(char* input, int lenght, int nbr);
void swap(char* input, int posA, int posB);
int findPos(char* input, int lenght, char cmp);
void partner(char* input, int lenght, char a, char b);
int getKeyValue(char* c);
void doMove(char* line, char* type, char* arg);
int readInput(char* input);
int seen(char* line, int row, int col, char seenBefore[][col], int nbrSeen);
void partTwo();

int main(void){
	char line[LENGTH+1];
	char dans[MAXINPUT];

	char ch = 'a';

	// fill with abcde....
	for(int i = 0; i < LENGTH; i++){
		line[i] = ch++;
	}

	line[LENGTH] = '\0';

	printf("Before %s\n", line);

	readInput(dans);

	// parse input string
	char* token;
	char* delimit = ",";
	token = strtok(dans, delimit);

	while(token){

		char move[1];

		move[0] = token[0];
		move[1] = '\0';

		char arg[10];
		strcpy(arg, ++token); // skip first character

		doMove(line, move, arg);
		token = strtok(NULL, delimit);
	}

	printf("After %s\n", line);

	partTwo();


}

void partTwo(){
	char line[LENGTH+1];
	char dance[MAXINPUT];
	char danceCopy[MAXINPUT];

	char inputLines[100][LENGTH+1];


	char ch = 'a';

	// fill with abcde....
	for(int i = 0; i < LENGTH; i++){
		line[i] = ch++;
	}

	line[LENGTH] = '\0';

	printf("Before %s\n", line);

	readInput(dance);

	int nbrSeen = 0;

	for(long long i = 0; i < 1000000000; i++){
		char* token;
		char* delimit = ",";
		strcpy(danceCopy, dance);
		token = strtok(danceCopy, delimit);


		if(seen(line, 100, LENGTH+1, inputLines, nbrSeen) >= 0){
			printf("Seen before %d\n", --nbrSeen);
			break;
		}else{
			strcpy(inputLines[nbrSeen], line);
			nbrSeen++;

			while(token){
				char move[1];
				move[0] = token[0];
				move[1] = '\0';
				char arg[10];

				strcpy(arg, ++token); // skip first character

				doMove(line, move, arg);
				token = strtok(NULL, delimit);
			}
		}
	}

	int p = (1000000000)%nbrSeen;


	printf("After %s\n", inputLines[p]);

}

/*
 * Check if the line have been seen before
 * Return 1 if true -1 if not true
 */
int seen(char* line, int row, int col, char seenBefore[][col], int nbrSeen){
	int pos = -1;

	for(int i = 0; i < nbrSeen; i++){
		if(strcmp(line, seenBefore[i]) == 0){
			return 1;
		}
	}

	return pos;
}

/*
 * Performs the spinn exchange and partner moves on the array
 */
void doMove(char* line, char* type, char* arg){

	char temp[6];
	strcpy(temp,arg);

	int key = getKeyValue(type);
	char chA, chB;

	int pos;
	switch (key){
	case SPINN:
		pos = atoi(arg);
		spinArray(line, strlen(line), pos);
		break;
	case EXCHANGE:
		temp[strcspn(temp, "/")] = 0;
		int posA, posB;

		sscanf(arg, "%d/%d", &posA, &posB);

		swap(line, posA, posB);
		break;
	case PARTNER:

		sscanf(temp, "%c", &chA);
		sscanf(temp+strcspn(temp, "/")+1, "%c", &chB);

		partner(line,strlen(line), chA, chB);
		break;
	default:
		printf("No move to preform\n");
		break;
	};
}

/*
 * Move character at position pos to front of list
 * The characters maintains their order after
 */
void spinArray(char* input, int lenght, int nbr){
	int newPos;
	char temp[lenght];

	for(int i = 0; i < lenght; i++){
		newPos = (i+nbr)%lenght;
		temp[newPos] = input[i];
	}

	for(int i = 0; i < lenght; i++){
		input[i] = temp[i];
	}

}

void swap(char* input, int posA, int posB){
	char temp = input[posA];
	input[posA] = input[posB];
	input[posB] = temp;
}

/*
 * Swap position of characters a and b in array
 */
void partner(char* input, int lenght, char a, char b){
	int posA = findPos(input, lenght, a);
	int posB = findPos(input, lenght, b);


	if(posA >= 0 && posB >= 0){
		swap(input, posA, posB);
	}else{
		fprintf(stderr, "Couldn't partner! Character not found in array\n");
	}
}

int getKeyValue(char* c){
	int value = 0;

	for(int i = 0; i < sizeof(stateTable)/sizeof(keyTableT); i++ ){
		if(strcmp(c, stateTable[i].key) == 0){
			value = stateTable[i].value;
		}
	}

	return value;
}

/*
 * Finds the position of a character in array and returns it's position
 * Returns -1
 */
int findPos(char* input, int lenght, char cmp){
	int pos = -1;

	for(int i = 0; i < strlen(input); i++){
		if(input[i] == cmp){
			pos = i;
		}
	}

	return pos;
}

int readInput(char* input){
	int lenght;
	int nbrRead = 0;
	char buffer[BUFFERSIZE];

	FILE* fp = fopen(FILENAME, "r");

	if(fp != NULL){
		while(fgets(buffer, sizeof(buffer)/sizeof(char), fp)){
			nbrRead++;
			if(nbrRead == 1){
				strcpy(input, buffer);
			}else{
				strcat(input, buffer);
			}

			lenght += strlen(buffer);
		}
	}else{
		fprintf(stderr, "Could not open file %s\n", FILENAME);
	}

	fclose(fp);

	return lenght;
}
