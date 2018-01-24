/*
 * day15.c
 *
 *  Created on: 19 jan. 2018
 *      Author: aumink
 *
 * Puzzle input
 * Generator A starts with 516
 * Generator B starts with 190
 */

#include <stdio.h>
#include <stdlib.h>

#define SEED_A 516
#define SEED_B 190

#define FACTOR_A 16807
#define FACTOR_B 48271
#define MULTIPEL_A 4
#define MULTIPEL_B 8

#define DIVISOR 2147483647
#define INTER_A 40000000
#define INTER_B 5000000

#define LOW16BITS 0xFFFF

unsigned long long generator(unsigned long long prev, unsigned long long factor);
unsigned long long generatorMultipel(unsigned long long prev, unsigned long long factor, unsigned int multipel);

int main(void){
	unsigned long long valueA = SEED_A;
	unsigned long long valueB = SEED_B;
	unsigned long long lowbitsA;
	unsigned long long lowbitsB;


	int nbrMatched = 0;

	// part one
	// find number of pairs with lowest 16

	for(unsigned long i = 1; i < INTER_A; i++){
		valueA = generator(valueA, FACTOR_A);
		valueB = generator(valueB, FACTOR_B);
		lowbitsA = valueA & LOW16BITS;
		lowbitsB = valueB & LOW16BITS;

		if(lowbitsA == lowbitsB){
			nbrMatched++;
		}
	}

	printf("Number of matching pairs in part one %d\n", nbrMatched);

	//part two
	valueA = SEED_A;
	valueB = SEED_B;
	nbrMatched = 0;

	for(unsigned long i = 1; i < INTER_B; i++){
		valueA = generatorMultipel(valueA, FACTOR_A, MULTIPEL_A);
		valueB = generatorMultipel(valueB, FACTOR_B, MULTIPEL_B);
		lowbitsA = valueA & LOW16BITS;
		lowbitsB = valueB & LOW16BITS;

		if(lowbitsA == lowbitsB){
			nbrMatched++;
		}
	}

	printf("Number of matching pairs in part two %d\n", nbrMatched);

}

/*
 * Number generator for part one
 */
unsigned long long generator(unsigned long long prev, unsigned long long factor){

	unsigned long long number = prev*factor%DIVISOR;

	return number;

}

/*
 * Number generator for part two
 */
unsigned long long generatorMultipel(unsigned long long prev, unsigned long long factor, unsigned int multipel){
	unsigned long long number;

	do{
		number = prev*factor%DIVISOR;
		prev = number;
	}while(number % multipel > 0);

	return number;
}
