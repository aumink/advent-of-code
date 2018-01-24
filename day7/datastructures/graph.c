/*
 * graph.c
 *
 * Created on : 23 dec. 2017
 * Author: aumink
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

typedef struct vertexTag{
	graphElementT element;
	int isVisited;
	struct edgeTag* parents;
	struct edgeTag* children;
	struct vertexTag* next;
} vertexT;

typedef struct edgeTag{
	vertexT* conectsTo;
	struct edgeTag* next;
} edgeT;

typedef struct graphCDT{
	vertexT *vertices;
} graphCDT;

static vertexT* createVertex(graphElementT* elem);
//static edgeT* createChild(vertexT* v, vertexT* child);
static void addChildToVertex(vertexT* v, vertexT* child);
static void addParentToVertex(vertexT* v, vertexT* parent);
static vertexT* findVertex(graphCDT* graph, char* name);
int balanced(vertexT* v);
void printVertex(vertexT* v);
int findConected(vertexT* node);

//void testGraph();


/*void set_std_buffer_off(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(void){
	set_std_buffer_off();
	testGraph();

}

void testGraph(){

	graphCDT* graph = createGraph();

	graphElementT* v1;
	v1 = createGraphElement("A", 1);

	addVertex(graph, v1);

	changeValues(v1, "B", 2);
	addVertex(graph, v1);
	changeValues(v1, "C", 3);
	addVertex(graph, v1);
	changeValues(v1, "D", 4);
	addVertex(graph, v1);


	addChildToName(graph, "A", "B");
	addChildToName(graph, "A", "C");
	addChildToName(graph, "B", "D");
	addChildToName(graph, "C", "D");


	findNoParent(graph);

	printChildren(graph);
	printParents(graph);
	printGraph(graph);

}*/

/*
 * Creates adjacent linked list of a graph
 */
graphCDT* createGraph(){
	graphCDT* graph = calloc(1, sizeof(graphCDT));

	return graph;
}

/*
 * Delete the graph and free memory
 */
void deleteGraph(graphCDT* g){
	vertexT* curr = g->vertices;
	vertexT* next;

	while(curr != NULL){
		next = curr->next;
		free(curr);
		curr = next;
	}

	g = NULL;
}

/*
 * Creates a vertex
 * Helper function to addVertex
 */
static vertexT* createVertex(graphElementT* elem){
	vertexT* node = calloc(1,sizeof(vertexT));

	if(node != NULL){
		node->element = *elem;
		node->isVisited = 0;
	}else{
		fprintf(stderr, "Calloc of vertex failed");
	}

	return node;
}


/*
 * Adds a vertex to the graph with name and weight
 * It adds vertexes to the tail
 */
void addVertex(graphCDT* graph, graphElementT* elem){

	vertexT* newElement = createVertex(elem);

	//inserts new node to list

	if(graph->vertices == NULL){ // special case list empty
		newElement->next = graph->vertices;
		graph->vertices = newElement;
	}else{
		vertexT* curr = graph->vertices;
		vertexT* tail = curr;

		while(curr != NULL){ // find end of list
			tail = curr;
			curr = curr->next;
		}

		// insert new node to end of list
		tail->next = newElement;
		newElement->next = NULL;
	}

}

/*
 * Add child edges to a vertex
 */
static void addChildToVertex(vertexT* v, vertexT* child){
	edgeT* newEdge;

	newEdge = calloc(1,sizeof(edgeT));
	if(newEdge == NULL){
		fprintf(stderr, "Malloc of child failed\n");
	}

	newEdge->conectsTo = child;

	newEdge->next = v->children;
	v->children = newEdge;
}

/*
 * Help function to addParents
 */
static void addParentToVertex(vertexT* v, vertexT* parent){
	if(parent != NULL){
		edgeT* newEdge;

		newEdge = calloc(1,sizeof(edgeT));
		if(newEdge == NULL){
			fprintf(stderr, "Malloc of child failed\n");
		}
		newEdge->conectsTo = parent;
		newEdge->next = v->parents;

		v->parents = newEdge;
	}
}

/*
 * Add a child to a  a vertex in graph
 */
void addChild(graphCDT* graph, graphElementT* parent, graphElementT* child){
	vertexT* p = findVertex(graph, getName(parent));
	vertexT* c = findVertex(graph, getName(child));

	addChildToVertex(p,c);
	addParentToVertex(c,p);
}

/*
 * Add a child to the parent vertex in graph
 */
void addChildToName(graphCDT* graph, char* parent, char* child){
	vertexT* p = findVertex(graph, parent);
	vertexT* c = findVertex(graph, child);

	addChildToVertex(p,c);
	addParentToVertex(c,p);
}

/*
 * Finds the vertex i graph witch matches name
 */
static vertexT* findVertex(graphCDT* graph, char* name){
	vertexT* curr = graph->vertices;

	while(curr != NULL){
		if(strcmp(getName(&curr->element), name) == 0){
			return curr;
		}else{
			curr = curr->next;
		}
	}

	printf("No match was found");
	return NULL;
}

/*
 * Print all vertices in a graph
 */

void printGraph(graphCDT* graph){
	vertexT* curr = graph->vertices;

	while(curr != NULL){
		printf("%s (%d)\n", curr->element.name, curr->element.weight);
		curr = curr->next;
	}
}


void printVertex(vertexT* v){
	vertexT* curr = v;

	while(curr != NULL){
		printf("%s (%d)\n", curr->element.name, curr->element.weight);
		curr = curr->next;
	}
}

/*
 * Prints the children of a graph
 */
void printChildren(graphCDT* graph){
	vertexT* v = graph->vertices;

	// walk through all vertices in a graph
	while(v != NULL){

		edgeT* curr = v->children;
		printf("Children to %s is ", getName(&v->element));

		if(curr == NULL){
			printf("Has no children");
		}

		// walk through all children to current vertex
		while(curr != NULL){
			if(curr->conectsTo != NULL){
				vertexT* child = curr->conectsTo;
				printf("%s ", getName(&child->element));
			}else{
				printf("Has no children");
			}

			curr = curr->next;
		}

		printf("\n");
		v = v->next;
	}
}

/*
 * Prints the parents in a graph
 */
void printParents(graphCDT* graph){
	vertexT* v = graph->vertices;

	// walk trough all vertices
	while(v != NULL){

		edgeT* curr = v->parents;
		printf("Parents to %s is ", getName(&v->element));

		if(curr == NULL){
			printf("Has no parents");
		}

		// walk trough all parents for current vertex
		while(curr != NULL){
			if(curr->conectsTo != NULL){
				vertexT* parent = curr->conectsTo;
				printf("%s ", getName(&parent->element));
			}else{
				printf("Has no parents");
			}

			curr = curr->next;
		}
		printf("\n");
		v = v->next;
	}
}

/*
 * Finds the vertex with no parents. Assumes all nodes are
 * Connected to root node
 */
char* findNoParent(graphCDT* graph){
	vertexT* curr = graph->vertices;
	vertexT* noParent;

	while(curr != NULL){

		edgeT* parent = curr->parents;

		if(parent == NULL){ // node have no parents
			noParent = curr;
		}

		curr = curr->next;
	}

	if(noParent != NULL){
		//printf("Vertex %s has no parents\n", getName(&noParent->element));
	}

	return getName(&noParent->element);


}

/*
 * Finds the level in subtree with element to change
 * One have to manualy find the correct answer from the node
 */

void isBalanced(graphCDT* graph, char* name){
	vertexT* node = findVertex(graph, name);
	edgeT* children = node->children;
	//int towerWeight = balanced(node);
	while(children != NULL){
		int towerWeight = balanced(children->conectsTo);
		name = getName(&(children->conectsTo)->element);
		printf("Tower %s weight is %d\n", name, towerWeight);
		children = children->next;

	}


}

/*
 * Finds the node with witch shall change in order to balance the tower
 */
int balanced(vertexT* v){
	edgeT* children = v->children;
	int currWeight, prevWeight;
	int totalWeight = getWeight(&v->element);
	int nbrChildren = 0;

	if(children == NULL){
		totalWeight = getWeight(&v->element);
	}

	while(children != NULL){ // for all children of node
		nbrChildren++;
		currWeight = balanced(children->conectsTo); // walk down in the tree

		if(nbrChildren == 1){ // special case if only one node
			prevWeight = currWeight;
			totalWeight+= currWeight;
		}else{
			if(currWeight == prevWeight){
				totalWeight += currWeight;
			}else{
				printf("Element c %d differs from p %d\n", currWeight, prevWeight);


				//add print function to see witch element c or p to change
			}
		}

		children = children->next;
	}

	return totalWeight;
}

/*
 * Calculates the number of nodes that are conected to name
 *
 */
int nbrConnectedNodes(graphCDT* graph, char* name){
	vertexT* curr = findVertex(graph, name);

	return findConected(curr);
}

/*
 * Help function to nbrConnectedNodes
 */
int findConected(vertexT* node){
	static int nbrConected = 1;
	node->isVisited = 1;

	edgeT* curr = node->parents;

	while(curr != NULL){
		if(curr->conectsTo->isVisited == 0){
			nbrConected++;
			findConected(curr->conectsTo);
		}
		curr = curr->next;
	}

	curr = node->children;

	while(curr != NULL){
		if(curr->conectsTo->isVisited == 0){
			nbrConected++;
			findConected(curr->conectsTo);
		}
		curr = curr->next;
	}

	return nbrConected;
}

/*
 * Finds the first vertex in graph that haven't been visited
 * and returns the name of that vertex
 * Returns a null pointer if not found
 */
char* findNotVisited(graphCDT* graph){
	vertexT* curr = graph->vertices;
	char* name;

	while(curr != NULL){
		if(curr->isVisited == 0){
			name = getName(&curr->element);
			return name;

		}else{
			curr = curr->next;
		}
	}

	return NULL;
}

/*
 * Set all nodes to not visited
 */
void restVisited(graphCDT* graph){
	vertexT* curr = graph->vertices;

	while(curr != NULL){
		curr->isVisited = 0;
		curr = curr->next;
	}
}


/*Get the graph elements name
 *
 */
char* getName(graphElementT* elem){
	return elem->name;
}

/*
 * Get graph elements weight
 */
int getWeight(graphElementT* elem){
	return elem->weight;
}

/*
 * Creates a graph element and returns a pointer to it;
 * Returns a NULL on failure
 */
graphElementT* createGraphElement(char *name, int w){
	graphElementT* elem = malloc(sizeof(graphElementT));
	if(elem != NULL){
		strcpy(elem->name, name);
		elem->weight = w;
	}else{
		fprintf(stderr, "Malloc of graphElement faild");
	}

	return elem;
}

/*
 * Changes the values of a graph element;
 */
void changeValues(graphElementT* g, char* name, int w){
	strcpy(g->name, name);
	g->weight = w;
}


