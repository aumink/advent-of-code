/*
 * linkedList.h
 *
 *  Created on: 26 dec. 2017
 *      Author: aumink
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct llistElementTag{
	char reg[10];
	int value;
} llistElementT;

typedef struct llistCDT
	llistCDT;

llistCDT* createList();
void addElement(llistCDT* list, llistElementT elem);
void printList(llistCDT* list);
int getNodeValue(llistCDT* list, char* regi);
int findMaxValue(llistCDT* list);
void updateReg(llistCDT* list, char* reg, int newValue);
void changeValue(llistElementT* elem, char* name,int value);
llistElementT* createListElem(char* name, int value);




#endif /* LINKEDLIST_H_ */
