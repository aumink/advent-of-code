/*
 * day1.c
 *
 * Created on : 12 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXBUFFER 10000

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

void readFromFile(const char* fileName, char* input){
	FILE *fp;


	fp = fopen(fileName, "r");

	if(fp != NULL){
		fgets(input, MAXBUFFER, fp);
		input[strcspn(input, "\n")] = 0; // delete ending newline from name
	}else{
		printf("Couldn't open file %s", fileName);
	}

	//return input;
}

int main(void){
	set_std_buffer_off();
	char input[MAXBUFFER];

	readFromFile("input1.txt", &input[0]);

	printf("Input %s\n", input);
	printf("Längd input = %d\n", strlen(input));

	int lenght = strlen(input);
	int sum = 0;

	// part one
	// sum adjecent elements that are equal in a circular list
	for(int i = 0; i < lenght; i++){
		int curr, currNext, nextIndex;

		curr = input[i]-'0'; // convert to int
		nextIndex = (i+1)%(lenght);
		currNext = input[nextIndex] - '0';


		if(curr == currNext){
			sum += curr;
		}
	}

	printf("Sum part one= %d\n", sum);

	//part two
	// sum elements that are halfway around the circular list

	int step = lenght/2;
	sum = 0;

	for(int i = 0; i < lenght; i++){
		int curr, currNext, nextIndex;

		curr = input[i]-'0'; // convert to int
		nextIndex = (i+step)%(lenght);
		currNext = input[nextIndex] - '0';

		if(curr == currNext){
			sum += curr;
		}
	}

	printf("Sum part two= %d\n", sum);

}
