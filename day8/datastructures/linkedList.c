/*
 * linkedList.c
 *
 * Created on : 26 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

typedef struct llistNodeTag{
	llistElementT element;
	struct llistNodeTag* next;
} llistNodeT;

typedef struct llistCDT{
	llistNodeT* head;
}	llistCDT;

static llistNodeT* createNode(llistElementT* elem);
static llistNodeT* findRegPos(llistCDT* list, char* name);
char* getName(llistNodeT* node);
int getValue(llistNodeT* node);


/*
 * Creates a linked list
 */
llistCDT* createList(){
	llistCDT* list = calloc(1, sizeof(llistCDT));

	if(list == NULL){
		fprintf(stderr, "Calloc of list head failed\n");
	}

	return list;
}

/*
 * Creates a list node and returns a pointer to it
 */

static llistNodeT* createNode(llistElementT* elem) {
	llistNodeT* node = calloc(1, sizeof(llistNodeT));

	if(node != NULL){
		node->element = *elem;
	}else{
		fprintf(stderr, "Calloc of createNode failed\n");
	}

	return node;
}

/*
 * Pushes an element to the head of list that is not already in the list
 */
void addElement(llistCDT* list, llistElementT elem){

	llistNodeT** head = &list->head;

	llistNodeT* newNode = createNode(&elem);


	if(findRegPos(list, getName(newNode)) == NULL){
		if(head == NULL){ // list empty
			*head = newNode;
		}else{
			newNode->next = *head;
			*head = newNode;
		}
	}
}


/*
 * Finds the node in list witch matches name
 * Returns pointer to node if found
 * Returns NULL pointer if name was not found in list
 */
static llistNodeT* findRegPos(llistCDT* list, char* name){
	llistNodeT* curr = list->head;

	while(curr != NULL){
		if(strcmp(curr->element.reg, name) == 0){ // found match
			return curr;
		}

		curr = curr->next;
	}

	return NULL;
}

/*
 * Finds maximum value stored in the list
 */
int findMaxValue(llistCDT* list){
	llistNodeT* curr = list->head;
	int max = 0;

	if(curr != NULL){
		max = getValue(curr);
	}

	int currValue = getValue(curr);
	while(curr != NULL){
		currValue = getValue(curr);
		if(currValue > max){
			max = currValue;
		}

		curr = curr->next;
	}

	return max;
}


/*
 * Print all vertices in a graph
 */

void printList(llistCDT* list){
	llistNodeT* curr = list->head;

	while(curr != NULL){
		printf("%s (%d)\n", curr->element.reg, curr->element.value);
		curr = curr->next;
	}
}

/*
 * Returns the name of a listElement
 */
char* getName(llistNodeT* node){
	return node->element.reg;
}

/*
 * Returns the value of listElement
 */

int getValue(llistNodeT* node){
	if(node != NULL){
		return node->element.value;
	}else{
		fprintf(stderr, "Could not retrieve listelement name\n");
		return 0;
	}
}

/*
 * Returns the value of the listnode matching regi
 */

int getNodeValue(llistCDT* list, char* regi){
	llistNodeT* node = findRegPos(list, regi);


	return node->element.value;

}

/*
 * Update the node with contaion rag with newValue
 */
void updateReg(llistCDT* list, char* reg, int newValue){
	llistNodeT* node = findRegPos(list, reg);

	node->element.value += newValue;
}

/*
 * Create a list element
 */
llistElementT* createListElem(char* name, int value){
	llistElementT* elem = malloc(sizeof(llistElementT));

	if(elem != NULL){
		strcpy(elem->reg, name);
		elem->value = value;
	}else{
		fprintf(stderr, "Malloc of listElementT failed\n");
	}

	return elem;
}

/*
 * Changes the value of a list element
 */
void changeValue(llistElementT* elem, char* name,int  value){
	strcpy(elem->reg, name);
	elem->value = value;
}
