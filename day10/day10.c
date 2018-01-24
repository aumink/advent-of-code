/*
 * day10.c
 * Solves puzzle ten Knot Hash of advent of code 2017
 * http://adventofcode.com/2017/day/10
 * Created on : 1 jan. 2018
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 256
#define ROUNDS 64
const int lenghtSuffix[] = {17, 31, 73, 47, 23};

void reverse(int* array, int startPos,  int length, int arrayLength);
void partOne();
void partTwo();
void convertInput(char* input, int* asciiValues, int length);


void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();

	partOne();

	partTwo();
}

/*
 * Solve part two of the puzzle
 */
void partTwo(){

	int sparseHash[SIZE];
	// initialize the sparse hash with values from 0..255
	for(int i = 0; i < SIZE; i++){
		sparseHash[i] = i;
	}


	char* inputStr = "102,255,99,252,200,24,219,57,103,2,226,254,1,0,69,216";

	int inputLenght = strlen(inputStr);

	// convert input to ASCII values and add suffix
	int asciiSize = inputLenght + sizeof(lenghtSuffix)/sizeof(int);
	int asciiValues[asciiSize];

	convertInput(inputStr, asciiValues, asciiSize);


	// generate sparse hash

	int sparsLength = sizeof(sparseHash)/sizeof(int);
	int currPos = 0;
	int skipSize = 0;


	for(int i = 0; i < ROUNDS; i++){

		for(int j = 0; j < asciiSize; j++){
			reverse(sparseHash, currPos, asciiValues[j], sparsLength);
			currPos += asciiValues[j] + skipSize;
			currPos = currPos%sparsLength; // warp around list
			skipSize++;
		}
	}

	// generate dense hash
	// each value in dense hash is a XOR
	// of a block of 16 consecutive values from sparse hash

	int denseHash[16];

	for(int i = 0; i < 16; i++){
		int sum = 0;
		for(int j = 16*i; j < (16*i+16); j++){
			sum^= sparseHash[j];
		}
		denseHash[i] = sum;
	}

	// print denseHash in hex format

	printf("%s becomes ",inputStr);
	for(int i = 0; i < sizeof(denseHash)/sizeof(int); i++){
		printf("%02x", denseHash[i]);
	}
}

/*
 * Solves part one of the puzzle
 */
void partOne(){
	int sparseHash[SIZE];

	for(int i = 0; i < SIZE; i++){
		sparseHash[i] = i;
	}

	int input[] = {102,255,99,252,200,24,219,57,103,2,226,254,1,0,69,216};

	int inputLength = sizeof(input)/sizeof(int);
	int sparseLength = sizeof(sparseHash)/sizeof(int);


	int currPos = 0;
	int skipSize = 0;
	for(int i = 0; i < inputLength; i++){

		reverse(sparseHash, currPos, input[i], sparseLength);
		currPos += input[i] + skipSize;
		currPos = currPos%sparseLength;
		skipSize++;
	}

	printf("\nThe multiplication of the first two elements is %d\n", sparseHash[0]*sparseHash[1]);

}

/*
 * Reverses a segment of length in an array starting at
 * position startPos. If the segment reaches the end of the array
 * it wraps around to the front.
 * The segment length can not be longer than the arrayLength
 */
void reverse(int* array, int startPos,  int length, int arrayLength){
	int temp;
	int newIndex = 0;
	int currIndex = startPos;
	for(int i = 0; i < length/2; i++){
		currIndex = (startPos+i)%arrayLength;
		newIndex = (startPos+(length-1-i))%arrayLength;
		temp = array[newIndex];
		array[newIndex] = array[currIndex];
		array[currIndex] = temp;
	}
}

/*
 * Converts input string to corresponding ASCII characters
 * and adds the length suffix values at the end
 */

void convertInput(char* input, int* asciiValues, int length){

	// convert characters to ASCII values
	int nbrCharacters = 0;

	for(int i = 0; *input != '\0'; i++){
		asciiValues[i] = *input;
		input++;
		++nbrCharacters;
	}

	// add length suffixes to the end

	for(int i = 0; i < sizeof(lenghtSuffix)/sizeof(int); i++){
		asciiValues[i+nbrCharacters] = lenghtSuffix[i]; // start at end of ascii values
	}


}

