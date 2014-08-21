#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// int main() {
// 	MyList * myList = newList();
// 	createAndAdd(myList,"Grandpa",0);
// 	createAndAdd(myList,"Grandma",1);
// 	createAndAdd(myList,"Mom",2);
// 	createAndAdd(myList,"Dad",3);
// 	listRemove(myList,findByValue(myList,3));

// 	ListElem * curr = getRoot(myList);
// 	while(curr != NULL) {
// 		printf("%s, %d\n", curr->name,curr->val);
// 		curr = curr->next;
// 	}
// }

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

ListElem * createNode(char nodeName[], long long int val) {
	ListElem * newElem = malloc(sizeof(ListElem));
	newElem->next = NULL;
	newElem->val = val;
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

ListElem * findByValue(MyList * list, long long int val) {
	if(listIsEmpty(list)) return NULL;
	ListElem * curr = getRoot(list);
	while(curr != NULL) {
		if(curr->val == val) return curr;
		curr = curr->next;
	}
	return NULL;
}

void createAndAdd(MyList * list, char name[], long long int val) {
	ListElem * newElem = createNode(name,val);
	listAdd(list,newElem);
}

bool listIsEmpty(MyList * list) {
	return list->head->next == NULL;
}

MyList * newList() {
	MyList * newList = malloc(sizeof(MyList));
	ListElem * Dummy = createNode("Dummy",0);
	listAdd(newList,Dummy);
	return newList;
}

void printList(MyList * list) {
	ListElem * curr = getRoot(list);
	while(curr != NULL) {
		printf("%s, %llu\n", curr->name,curr->val);
		curr = curr->next;
	}
}


