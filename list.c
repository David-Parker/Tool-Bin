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
		list->tail = newElem;
	}
	else {
		list->tail->next = newElem;
		list->tail = newElem;
	}
}

void listRemove(MyList * list, ListElem * rmElem) {
	if(listIsEmpty(list) || rmElem == NULL) return;

	ListElem * curr = list->head;
	ListElem * next = curr->next;
	while(next) {
		if(next == rmElem) {
			if(next == list->tail) list->tail = curr;
			curr->next = next->next;
			free(next);
			return;
		}
		curr = next;
		next = curr->next;
	}
}

/* User Utility Functions */

ListElem * getRoot(MyList * list) {
	if(listIsEmpty(list)) return NULL;
	else return list->head->next;
}

ListElem * createNode(char nodeName[]) {
	ListElem * newElem = malloc(sizeof(ListElem));
	newElem->next = NULL;
	strcpy(newElem->name,nodeName);
	return newElem;
}

ListElem * findByName(MyList * list, char name[]) {
	if(listIsEmpty(list)) return NULL;
	ListElem * curr = getRoot(list);
	while(curr != NULL) {
		if(!strcmp(curr->name,name)) return curr;
		curr = curr->next;
	}
	return NULL;
}

void createAndAdd(MyList * list, char name[]) {
	ListElem * newElem = createNode(name);
	listAdd(list,newElem);
}

bool listIsEmpty(MyList * list) {
	return list->head->next == NULL;
}

MyList * newList() {
	MyList * newList = malloc(sizeof(MyList));
	ListElem * Dummy = createNode("Dummy");
	listAdd(newList,Dummy);
	return newList;
}


