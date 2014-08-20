#include <stdbool.h>
#ifndef LIST_H
#define LIST_H
/* Type Definitons */
typedef struct ListElem {
	char name[64];
	int val;
	struct ListElem *next;
} ListElem;

typedef struct List {
	/* Head is always a dummy node if initialized with newList() */
	/* To get the actual root, use getRoot() */
	struct ListElem * head;
	struct ListElem * tail;
} MyList;

/* Func Protos */
void listAdd(MyList * list, ListElem * newElem);
void listRemove(MyList * list, ListElem * rmElem);
ListElem * createNode(char nodeName[], int val);
ListElem * findByName(MyList * list, char name[]);
ListElem * findByValue(MyList * list, int val);
ListElem * getRoot(MyList * list);
bool listIsEmpty(MyList * list);
void createAndAdd(MyList * list, char name[], int val);
MyList* newList();

#endif