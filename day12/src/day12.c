/*
 * day12.c
 * http://adventofcode.com/2017/day/12
 * Created on : 9 jan. 2018
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <string.h>

#define INPUT "input12.txt"
#define MAXBUFFER 1024

int readInput(graphCDT *input);
void addConections(graphCDT* graph, char* vertex, char* buffer);
int nbrOfGroups(graphCDT* graph);

void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();

	graphCDT* graph = createGraph();

	readInput(graph);

	printf("Number of nodes connected to 0 is %d\n", nbrConnectedNodes(graph, "0"));

	printf("Number of groups are %d\n", nbrOfGroups(graph));

}

/*
 * Reads vertex name from file and stores in a graph
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

		graphElementT* element = createGraphElement("a", weight);

		// adds vertices from file
		while(fgets(buffer, MAXBUFFER, fp) != NULL){

			sscanf(buffer,"%s", name);

			changeValues(element,name, weight);

			addVertex(input,element);

			index++;
		}

		// set connections between vertices
		rewind(fp);
		while(fgets(buffer, MAXBUFFER, fp) != NULL){

			buffer[strcspn(buffer, "\n")] = 0; // delete new line
			sscanf(buffer,"%s", name);

			// find pos in buffer where connections are listed
			size_t n = strcspn(buffer, ">");
			addConections(input, name, &buffer[++n]);
		}

	}
	else{
		fprintf(stderr, "Failed to open file\n");
		exit(1);
	}

	fclose(fp);

	return index;
}

/*
 * Add connections to vertices
 */

void addConections(graphCDT* graph, char* vertex, char* buffer){
	char* delimit = ", ";
	char* token = strtok(++buffer, delimit);

	while(token){

		addChildToName(graph, vertex, token);
		token = strtok(NULL,delimit);
	}

}

/*
 * Solve part two of puzzle
 * Calculates number of groups in graph
 * All nodes in graph must be set to not visited for calculation to work
 */
int nbrOfGroups(graphCDT* graph){

	restVisited(graph);

	char* name;
	name = findNotVisited(graph);
	int nbrGroupes = 0;

	while(name != NULL){
		nbrConnectedNodes(graph, name);
		nbrGroupes++;
		name = findNotVisited(graph);
	}

	restVisited(graph);

	return nbrGroupes;
}

