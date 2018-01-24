/*
 * day2.c
 *
 * Advent of code puzzel nr 2
 * Calculate checksum of rows in a spreadsheet
 * The checksum is the difference between the largest and smallest
 * value in a row
 *
 * Created on : 13 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAXINPUT  1024

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

void readFromFile(char* list, char* fileName);
int getRowDiff(char* row, int lenght);
int getRowDivEven(char* row, int lenght);
int nbrElements(char* str, char delimit);
int getEven(int a, int b);

int main(void){
	set_std_buffer_off();

	char row[MAXINPUT];

	readFromFile(&row[0], "input3.txt");


}

/*
 * Part 1
 * Calculate the difference beetween min and max values in a string
 * where values are seperated by whitespaces
 * 1 2.....3 4
 */
int getRowDiff(char* row, int lenght){
	unsigned int min = UINT_MAX;
	unsigned int max = 0;
	char* delimit = "\t";

	char *number = strtok(row, delimit);

	while(number){
		//printf("%s\n", number);
		int value = atoi(number);

		if(value > max){
			max = value;
		}

		if(value < min){
			min = value;
		}

		number = strtok(NULL, delimit);
	}

	return (max - min);

}

/*
 * Part 2
 * Finds even divisiable numbers in a string values in a string
 * where values are seperated by whitespaces
 * 1 2.....3 4
 */
int getRowDivEven(char* row, int lenght){

	char* delimit = "\t";

	int nbrElement = nbrElements(row, *delimit);
	int rowArray[nbrElement];


	char *number = strtok(row, delimit);

	int i = 0;
	int result = 0;

	while(number){

		rowArray[i++] = atoi(number);

		number = strtok(NULL, delimit);
	}

	for(int i = 0; i < nbrElement; i++){
		for(int j = i+1; j < nbrElement; j++){
			result = getEven(rowArray[i], rowArray[j]);
			if(result > 0){
				return result;;
			}

		}
	}

	return result;
}

/*
 * Divides a / b and returns the resulst if the devision is even
 * Returns 0 for non even division
 */

int getEven(int a, int b){

	int result = 0;

	if(a > b && b != 0){

		if(a % b == 0){
			result = a / b;
		}
	}
	else if(a < b && a != 0){
		if(b % a == 0){
			result = b / a;
		}
	}

	return result;
}


/*
 * Reads input from a file and store values in an array
 */
void readFromFile(char* buffer, char* fileName){

	FILE *fp;

	fp = fopen(fileName, "r");

	int chksum = 0;
	int divsum = 0;

	if(fp != NULL){
		char copyBuffer[MAXINPUT];
		while(fgets(buffer, MAXINPUT, fp) != NULL){
			strcpy(copyBuffer, buffer);

			chksum += getRowDiff(copyBuffer, strlen(copyBuffer));
			divsum += getRowDivEven(buffer, strlen(buffer));
		}

	}

	printf("chksum = %d\n", chksum);
	printf("divsum = %d\n", divsum);

	fclose(fp);
}

/*
 * Count's nbr of elements in a row
 * The rows are assumed to have at least one element
 */
int nbrElements(char* str, char delimit){
	int nbr = 0;

	while(*str != '\0'){
		if(*str == '\t'){
			nbr++;
		}
		str++;
	}

	return nbr+1; // +1 since rows terminate with \n and not \t

}
