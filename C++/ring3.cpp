#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "windows.h"
#include <iostream>
#include <ostream>
#include <string>

std::string GetClipboardText();
void SetClipboardText();
char *strtok_r (char *s,const char *delim,char **save_ptr);

using namespace std;
char final_str[10000] = "";

int main(int argc, char* argv[]) {
	/* This program is not safe to use where security is a concern */

	char str[10000];
	char* new_str;
	char* pch;
	char line[10000];
	char* realLine;
	char type[5];
	bool skip = 0;
	char curr = '.';

	std::string clip = GetClipboardText();
	strcpy(str,clip.c_str());
	/* This is not safe */
	memcpy(str,&str[0],10000);
	str[9999] = '\0';

	char* endTokenOuter;
	realLine = strtok_r(str,"\n",&endTokenOuter);

	while(realLine) {\
		char name[10000];
		int i = 0;

		strcat(final_str,"\"\"\"\"\"\"\t");
		char* endTokenInner;
		strcpy(line,realLine);
		//printf("%s\n", line);
		pch = strtok_r(line,"\t",&endTokenInner);

		while(pch) {
			if(i == 0)
				strcpy(name,pch);
			else if(i == 1)
				strcpy(line,pch);
			i++;
			pch = strtok_r(NULL,"\t",&endTokenInner);
		}

		/* fix the type */
		for(int j = 0; j < strlen(line); j++) {
			type[j] = line[j];
		}

		type[4] = '\0';

		printf("%s\n", name);

		i = 0;
		strcat(final_str,"in:");
		strcat(final_str,name);

		//printf("%s\n", line);

		if(!strcmp(type,"Bool")) {
			strcat(final_str,":bool:Enabled Disabled");
		}

		else if(!strcmp(type,"Inte")) {
			strcat(final_str,":int");
		}

		else if(!strcmp(type,"Doub")) {
			strcat(final_str,":double");
		}

		else if(!strcmp(type,"Stri")) {
			strcat(final_str,":string");
		}

		/* Ring lol */
		else {
			/* Never actually do this */
			memcpy(line,&line[6],10000 - 6);
			strcat(final_str,":ring:");

			while(curr != '\0') {
				curr = line[i];
				if(curr == ',') line[i] = '|';
				else if(curr == ')') line[i] = '\0';
				i++;
			}
			strcat(final_str,line);
		}
		//printf("%s\n", line);

		strcat(final_str,"\n");
		realLine = strtok_r(NULL,"\n",&endTokenOuter);
	}

	//printf("%s\n", final_str);
	SetClipboardText();
}

std::string GetClipboardText()
{
  // Try opening the clipboard
  if (!OpenClipboard(NULL)) printf("Error");

  // Get handle of clipboard object for ANSI text
  HANDLE hData = GetClipboardData(CF_TEXT);
  if (hData == NULL) printf("Error");

  // Lock the handle to get the actual text pointer
  char * pszText = static_cast<char*>( GlobalLock(hData) );
  if (pszText == NULL) printf("Error");

  // Save text in a string class instance
  std::string text( pszText );

  // Release the lock
  GlobalUnlock( hData );

  // Release the clipboard
  CloseClipboard();

  return text;
}

void SetClipboardText() {
	const size_t len = strlen(final_str) + 1;
	HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), final_str, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}

char *strtok_r (char *s,const char *delim,char **save_ptr) {
char *token;

	if (s == NULL)
		s = *save_ptr;

	/* Scan leading delimiters. */
	s += strspn (s, delim);
	if (*s == '\0')
		return NULL;

	/* Find the end of the token. */
	token = s;
	s = strpbrk (token, delim);
	if (s == NULL)
	/* This token finishes the string. */
		*save_ptr = strchr (token, '\0');
	else
	{
		/* Terminate the token and make *SAVE_PTR point past it. */
		*s = '\0';
		*save_ptr = s + 1;
	}
	return token;
}
