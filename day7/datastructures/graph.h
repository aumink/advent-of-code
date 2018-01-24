/*
 * graph.h
 *
 *  Created on: 23 dec. 2017
 *      Author: aumink
 */

#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct graphElementTag{
	int weight;
	char name[100];
} graphElementT;


typedef struct graphCDT
	graphCDT;


/*
 * Creates a graph
 */
graphCDT* createGraph();
void addVertex(graphCDT* graph, graphElementT* elem);
void addChild(graphCDT* graph, graphElementT* parent, graphElementT* child);
void addChildToName(graphCDT* graph, char* parent, char* child);
void printGraph(graphCDT* graph);
void printChildren(graphCDT* graph);
void printParents(graphCDT* graph);
char* findNoParent(graphCDT* graph);
void isBalanced(graphCDT* graph, char* name);
int nbrConnectedNodes(graphCDT* graph, char* name);
char* findNotVisited(graphCDT* graph);
void restVisited(graphCDT* graph);


//Graph element functions
graphElementT* createGraphElement(char *name, int w);
void changeValues(graphElementT* g, char* name, int w);
int getWeight(graphElementT* elem);
char* getName(graphElementT* elem);



//vertexT* createGraph();
//void addVertex(vertexT** head, int w, char* n);
//void addEdges(vertexT* v, vertexT* p, vertexT* c);
//void findNoParent(vertexT* v);
//vertexT* findChild(vertexT* graph, char* name);

//void printGraph(vertexT* graph);
//void printChildren(vertexT* graph);
//void printParent(vertexT* v);
//void testGraph();

#endif /* GRAPH_H_ */
