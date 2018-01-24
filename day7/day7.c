/*
 * day7.c
 * Find puzzle at http://adventofcode.com/2017/day/7
 * Created on : 22 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

#define INPUT "input7.txt"
#define MAXBUFFER 1024

int readInput(graphCDT* input);
void readChild(graphCDT* input);


void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();
	graphCDT* graph = createGraph();

	readInput(graph); // read vertices and weight
	readChild(graph); // add children to vertices

	char* name = findNoParent(graph);

	printf("Tree root is %s\n", name);
	isBalanced(graph, name);

}


/*
 * Reads vertex name and weight from file and stores in a graph
 * Input is separated by tabs "\t"
 *
 */
int readInput(graphCDT *input){

	FILE *fp;

	fp = fopen(INPUT, "r");

	char buffer[MAXBUFFER];

	int index = 1;

	if(fp != NULL){

		char name[10];
		int weight=0;

		graphElementT* element = createGraphElement("a", 0);

		while(fgets(buffer, MAXBUFFER, fp) != NULL){

			sscanf(buffer,"%s", name);
			int n = strcspn(buffer, "1234567890");
			sscanf(&buffer[n], "%d", &weight);

			changeValues(element,name, weight);

			addVertex(input,element);

			index++;
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
 * Read in the tree structure from file.
 * The children starts after -> axnd, cjkdf, jdflkfj,
 */
void readChild(graphCDT* input){

	FILE *fp;

	fp = fopen(INPUT, "r");

	char buffer[MAXBUFFER];

	if(fp != NULL){

		char name[10];

		while(fgets(buffer, MAXBUFFER, fp) != NULL){

			sscanf(buffer,"%s", name);

			//children starts after -> in input file
			const char *dstart = ">";
			size_t pos = strcspn(buffer, dstart); //posistion of ">" in buffer

			if(pos != strlen(buffer)){
				char children[MAXBUFFER];
				buffer[strcspn(buffer, "\n")] = 0; // delete new line

				strcpy(children, &buffer[pos+1]);

				char* token = strtok(&buffer[pos+1], ", ");

				while(token){
					char* child = token;

					addChildToName(input,name, child);

					token = strtok(NULL, ", ");
				}

			}

		}
	}
	else{
		fprintf(stderr, "Failed to open file\n");
		//exit(1);
	}

	fclose(fp);

}

