/*
 * fourthadvent.c
 *
 * Created on : 17 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXBUFFER 1024

void readFromFile(char* buffer, int length);
int chkPassPhrase(char *buffer, int lenght);
int getNbrWords(char* buffer);
int compareChar(const void *a, const void *b);
int chkPassPhraseAnnagram(char *buffer, int lenght);

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();
	char buffer[MAXBUFFER];
	readFromFile(buffer, MAXBUFFER);

}

void readFromFile(char* buffer, int length){
	FILE *fp;
	char* fileName = "input4.txt";

	fp = fopen(fileName, "r");
	int nbrCorrect = 0;
	int nbrAnagram = 0;

	if(fp != NULL){
		while(fgets(buffer, length, fp) != NULL){
			buffer[strcspn(buffer, "\n")] = 0; // delete ending newline from name
			//nbrCorrect += chkPassPhrase(buffer, length);
			nbrAnagram += chkPassPhraseAnnagram(buffer, length);
			//printf("Row %d has %d words\n", ++i, getNbrWords(buffer));
		}

	}
	else{
		printf("Couldn't open file\n %s", fileName);
	}

	printf("Number of valid passphrases %d\n", nbrCorrect);
	printf("Number of valid passphrases anagram %d\n", nbrAnagram);

}

int chkPassPhrase(char *buffer, int lenght){

	char* delimit = " ";

	int nbrWords = getNbrWords(buffer);

	//printf("nbrWrods %d\n", nbrWords);

	char* passPhrase[nbrWords];

	char *word = strtok(buffer, delimit);

	// move  buffer to a pointer array
	for(int i = 0; word; i++){
		passPhrase[i] = word;
		word = strtok(NULL, delimit); // get next word
		//printf("Pp %d is %s\n", i, passPhrase[i]);
	}

	// search for match

	int correct = 1; // set to passphrase to valid

	for(int i = 0; (i < nbrWords-1) && correct == 1; i++){
		for(int j = i+1; (j < nbrWords) && correct == 1; j++){

			if(strlen(passPhrase[i]) == strlen(passPhrase[j])){
				//check if words in passPhrase are identical
				char* match = strstr(passPhrase[j], passPhrase[i]);

				if(match == NULL){
					correct = 1;
				}else{
					correct = 0;
				}
			}
		}
	}


	if(correct > 0){
		//printf("Passphrase %s is valid\n", buffer);
	}

	return correct;
}

int chkPassPhraseAnnagram(char *buffer, int lenght){

	char input[lenght];
	strcpy(input, buffer);

	//printf("Input = %s\n", input);

	char* delimit = " ";

	int nbrWords = getNbrWords(buffer);

	//printf("nbrWrods %d\n", nbrWords);

	char* passPhrase[nbrWords];

	char *word = strtok(buffer, delimit);

	// move  buffer to a pointer array
	for(int i = 0; word; i++){
		passPhrase[i] = word;
		word = strtok(NULL, delimit); // get next word
		//printf("Pp %d is %s\n", i, passPhrase[i]);
	}


	// move buffer to char array
	char str[nbrWords][100];
	int passLenght = 0;

	for(int i = 0; i < nbrWords; i++){
		passLenght = strlen(passPhrase[i]);

		strcpy(str[i], passPhrase[i]);
		//printf("Före qsort = %s\n", str[i]);
		qsort(str[i], passLenght, sizeof(char), compareChar);
		//printf("Efter qsort = %s\n", str[i]);
	}


	// search for match

	int correct = 1; // set to passphrase to valid

	for(int i = 0; (i < nbrWords-1) && correct == 1; i++){
		for(int j = i+1; (j < nbrWords) && correct == 1; j++){
			int match = strcmp(str[i],str[j]);
			//printf("Str[%d] %s och str[%d] %s ger Match = %d\n",i,str[i],j, str[j], match);

			if(match != 0){
				correct = 1;
			}else{
				correct = 0;
			}
		}
	}


	if(correct > 0){
		//printf("Passphrase %s is valid\n", input);
	}

	return correct;
}
/*
 * Returns number of words in a non empty buffer
 * Assumes every row has at least one word
 */

int getNbrWords(char* buffer){
	int nbrWords = 0;

	char delimt = ' ';
	const char* result = buffer;

	while((result = strchr(result, delimt)) != NULL){
		nbrWords++;
		result++;
	}

	// add one extra since rows terminate with '\0'


	return nbrWords +1;
}

int compareChar(const void *a, const void *b){
	char arg1 = *(const char*)a;
	char arg2 = *(const char*)b;

	if(arg1 < arg2){
		return -1;
	}else if(arg1 > arg2){
		return 1;
	}else{
		return 0;
	}

}


