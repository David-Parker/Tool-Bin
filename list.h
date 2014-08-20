#ifndef LIST_H
#define LIST_H
/* Type Definitons */
typedef struct ListElem {
	char name[64];
	struct ListElem *next;
} ListElem;

typedef struct List {
	struct ListElem * head;
	struct ListElem * tail;
} MyList;

/* Func Protos */
void listAdd(MyList * list, ListElem * newElem);
void listRemove(MyList * list, ListElem * rmElem);
ListElem * createNode(char nodeName[]);
ListElem * getRoot(MyList * list);
void createAndAdd(MyList * list, char name[]);
MyList* newList();

#endif
