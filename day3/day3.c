/*
 * thridadvent.c
 *
 * Solves puzzel 3 on advent of code
 * http://adventofcode.com/2017/day/3
 *
 * Created on : 16 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>

void partOne();
void printGrid(int nRows, int nCols, int matrix[][nCols]);
void gridSpiral(int xpos, int ypos, int nRows, int nCols, int matrix[][nCols],int input);
int getSum(int xpos, int ypos, int nRows, int nCols, int matrix[][nCols]);

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){

	set_std_buffer_off();

	int input = 347991; // puzzel input
	printf("Number = %d\n", input);

	partOne();


	// part two

	// find which square ring input is on

	int n = 1;
	int ring = 1;
	while( n*n < input){
		n += 2;
		ring++;
	}

	int size = ring+1; // add extra ring to help with calculations

	int grid[size][size];
	int value = 0;

	// set all values to zero
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			grid[i][j] = value;

		}
	}

	// set start point and it's value
	grid[size/2][size/2] = 1;

	//Calculate first value greater than input in spiral

	gridSpiral(size/2, size/2, size, size, grid, input);

}

/*
 * Walks through the matrix i an outwards spiral of type
 * 17 16 15 14 13
 * 18  5  4  3 12
 * 19  6  1  2 11
 * 20  7  8  9 10
 * 21 22 23 -->
 *
 *  and sums up the sum of adjacent neighbors
*/

void gridSpiral(int xpos, int ypos, int nRows, int nCols, int matrix[][nCols], int value){

	int xDrec = 1; // 1 == move right -1 == move left
	int yDrec = -1; // 1 == move down -1 move up

	int stepLength = 1;
	int totalSteps = 1;

	// calculates value in matrix unto the first value larger than value
	while(matrix[ypos][xpos] < value){

		// move in x direction

		for(int i = 0; i < stepLength && matrix[ypos][xpos] <= value; i++){
			xpos = xpos+xDrec;
			matrix[ypos][xpos] = getSum(ypos,xpos, nRows, nCols, matrix);
			++totalSteps;
		}

		// move in y direction
		for(int i = 0; i < stepLength && matrix[ypos][xpos] <= value; i++){
			ypos = ypos + yDrec;
			matrix[ypos][xpos] = getSum(ypos,xpos, nRows, nCols, matrix);
			++totalSteps;
		}

		xDrec *= -1; // flip direction
		yDrec *= -1; // flip direction

		stepLength++;
	}

	printf("Sum = %d", matrix[ypos][xpos]);
}

/*
 * Sums the values of all adjacent neighbors to a point in the matrix
 * Assumes that the matrix is padded with 0 outside NxN
 */
int getSum(int xpos, int ypos, int nRows, int nCols, int matrix[][nCols]){
	int sum = 0;
	int xStart = xpos -1;
	int yStart = ypos -1;
	int xStopp = xpos +1;
	int yStopp = ypos +1;

	for(int i = xStart; i <= xStopp; i++){
		for(int j = yStart; j <= yStopp; j++){
			sum += matrix[i][j];
		}
	}

	return sum;
}

/*
 * Prints value in matrix of size nRows x nCols
 */
void printGrid(int nRows, int nCols,int matrix[][nCols]){
	for(int i = 0; i < nRows; i++){
		for(int j = 0; j < nCols; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
 * Calculate the Manhattan distance from input to center of matrix
 */

void partOne(){

	int number = 347991;

	// find which square ring number is on

	int n = 1;
	int ring = 1;

	while( n*n < number){
		n += 2;
		ring++;
	}

	printf("N = %d ring = %d\n", n, ring);

	// set nearest corner as pivot
	int pivot = n*n;
	for(int i = 0; n*n - (n-1)*i > number; i++){
		pivot = n*n - (n-1)*i;
	}

	printf("Pivot = %d\n", pivot);

	int dist = (ring-1)+(ring-1)-(pivot-number);

	printf("Dist %d\n", dist);

}
