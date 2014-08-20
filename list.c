#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {
	MyList * myList = newList();
	createAndAdd(myList,"Grandpa");
	createAndAdd(myList,"Grandma");
	createAndAdd(myList,"Mom");
	createAndAdd(myList,"Dad");

	ListElem * curr = getRoot(myList);
	while(curr != NULL) {
		printf("%s\n", curr->name);
		curr = curr->next;
	}
}

void listAdd(MyList * list, ListElem * newElem) {
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

void listRemove(MyList * list, ListElem * rmElem) {
	ListElem * curr = getRoot(list);
	while(curr != NULL) {
		curr = curr->next;
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
	listAdd(list,newElem);
}

MyList * newList() {
	MyList * newList = malloc(sizeof(MyList));
	newList->head = NULL;
	return newList;
}


