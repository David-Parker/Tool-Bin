#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* General Purpose list class developed by David Parker */

void listAdd(List * list, ListElem * newElem) {
	if(list->head == NULL) {
		list->head = newElem;
		list->tail = newElem;
	}
	else {
		list->tail->next = newElem;
		list->tail = newElem;
	}
}

void listRemove(List * list, ListElem * rmElem, bool destroy) {
	if(listIsEmpty(list) || rmElem == NULL) return;

	ListElem * curr = list->head;
	ListElem * next = curr->next;
	while(next) {
		if(next == rmElem) {
			if(next == list->tail) list->tail = curr;
			curr->next = next->next;
			if(destroy) free(next);
			return;
		}
		curr = next;
		next = curr->next;
	}
}

/* User Utility Functions */

ListElem * pop(List * list) {
	if(listIsEmpty(list)) return NULL;

	ListElem * temp = list->tail;
	listRemove(list,list->tail,false);
	return temp;
}

ListElem * getRoot(List * list) {
	if(listIsEmpty(list)) return NULL;

	else return list->head->next;
}

ListElem * createNode(char nodeName[], long long int val) {
	ListElem * newElem = calloc(1,sizeof(ListElem));
	newElem->next = NULL;
	newElem->val = val;
	strcpy(newElem->name,nodeName);
	return newElem;
}

ListElem * findByName(List * list, char name[]) {
	if(listIsEmpty(list)) return NULL;

	ListElem * curr = getRoot(list);
	while(curr != NULL) {
		if(!strcmp(curr->name,name)) return curr;
		curr = curr->next;
	}
	return NULL;
}

ListElem * findByValue(List * list, long long int val) {
	if(listIsEmpty(list)) return NULL;

	ListElem * curr = getRoot(list);
	while(curr != NULL) {
		if(curr->val == val) return curr;
		curr = curr->next;
	}
	return NULL;
}

void createAndAdd(List * list, char name[], long long int val) {
	ListElem * newElem = createNode(name,val);
	listAdd(list,newElem);
}

bool listIsEmpty(List * list) {
	return list->head->next == NULL;
}

List * newList() {
	List * newList = calloc(1,sizeof(struct List));
	ListElem * Dummy = createNode("Dummy",0);
	listAdd(newList,Dummy);
	return newList;
}

void printList(List * list) {
	ListElem * curr = getRoot(list);
	while(curr != NULL) {
		printf("%s, %llu\n", curr->name,curr->val);
		curr = curr->next;
	}
}


