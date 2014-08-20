#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Func Protos */
typedef struct ListElem {
	char name[64];
	struct ListElem *next;
} ListElem;

typedef struct List {
	struct ListElem * head;
	struct ListElem * tail;
} MyList;

void add(MyList * list, ListElem * newElem);
ListElem * createNode(char nodeName[]);
ListElem * getRoot(MyList * list);
void createAndAdd(MyList * list, char name[]);
MyList* newList();

int main() {
	MyList * myList = newList();
	createAndAdd(myList,"Grandpa");
	createAndAdd(myList,"Grandma");

	ListElem * curr = getRoot(myList);
	while(curr != NULL) {
		printf("%s\n", curr->name);
		curr = curr->next;
	}
}

void add(MyList * list, ListElem * newElem) {
	if(list->head == NULL) {
		list->head = newElem;
		list->tail = list->head;
		list->head->next = list->tail;
	}
	else {
		list->tail->next = newElem;
		list->tail = newElem;
	}
}

ListElem * getRoot(MyList * list) {
	return list->head;
}

ListElem * createNode(char nodeName[]) {
	ListElem * newElem = malloc(sizeof(ListElem));
	newElem->next = NULL;
	strcpy(newElem->name,nodeName);
	return newElem;
}

void createAndAdd(MyList * list, char name[]) {
	ListElem * newElem = createNode(name);
	add(list,newElem);
}

MyList * newList() {
	MyList * newList = malloc(sizeof(MyList));
	newList->head = NULL;
	return newList;
}


