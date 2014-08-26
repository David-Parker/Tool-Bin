#include <stdbool.h>
#ifndef LIST_H
#define LIST_H
/* Type Definitons */
typedef struct ListElem {
	char name[64];
	long long int val;
	struct ListElem *next;
} ListElem;

typedef struct List {
	/* Head is always a dummy node if initialized with newList() */
	/* To get the actual root, use getRoot() */
	struct ListElem * head;
	struct ListElem * tail;
} List;

/* Func Protos */
void listAdd(List * list, ListElem * newElem);
void listRemove(List * list, ListElem * rmElem, bool destroy);
ListElem * createNode(char nodeName[], long long int val);
ListElem * findByName(List * list, char name[]);
ListElem * findByValue(List * list, long long int val);
ListElem * pop(List * list);
ListElem * getRoot(List * list);
bool listIsEmpty(List * list);
void createAndAdd(List * list, char name[], long long int val);
List * newList();
void printList(List * list);

#endif
