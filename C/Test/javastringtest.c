#include <stdio.h>
#include <stdlib.h>
#include "String/javastring.h"

/* Func Protos */
void perm(String curr, String str, int index);


int main() {

	String foo = newString("This is FOO!");
	foo = foo.insertCharAt(&foo,'a',foo.length(&foo) - 1);
	foo.printString(&foo);


	foo = foo.substring(&foo,8,10);
	foo.printString(&foo);

	String bar = newString(" BAR");
	foo = foo.concat(&foo,&bar);
	foo.printString(&foo);

	StringArr foobar = split(&foo, " ");
	printf("%s\n",foobar[0]);
	printf("%s\n",foobar[1]);

	foo = foo.toLowerCase(&foo);
	bar = bar.toLowerCase(&bar);
	bar = bar.removeSpaces(&bar);
	foo.printString(&foo);
	bar.printString(&bar);

	if(foo.equals(&foo,&bar))
		printf("Same!\n");
	else
		printf("Not the same!\n");

	bar = newString("foo");

	if(foo.equals(&foo,&bar))
		printf("Same!\n");
	else
		printf("Not the same!\n");

	foo = foo.reverse(&foo);
	foo.printString(&foo);

	printf("%c\n",foo.charAt(&foo,1));

	bar = newString("bar");
	bar = bar.toUpperCase(&bar);
	printString(&bar);

}

void perm(String curr, String str, int index) {
	if(index == 0) ;//printString(&curr);

	else {
		for(int i = 0; i < index; i++) {
			String new_curr = curr.insertCharAt(&curr,str.text[i],curr.length(&curr));
			String new_str = str.removeCharAt(&str,i);
			perm(new_curr,new_str,index - 1);
		}
	}
}










