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

using namespace std;
char final_str[1024] = "";

int main(int argc, char* argv[]) {
	/* This program is not safe to use where security is a concern */
	char str[512];
	char* new_str;
	bool skip = 0;
	int i = 0;
	char curr = '.';

	std::string clip = GetClipboardText();
	strcpy(str,clip.c_str());
	/* This is not safe */
	memcpy(str,&str[6],500);

	while(curr != '\0') {
		curr = str[i];
		if(curr == ',') str[i] = '|';
		else if(curr == ')') str[i] = '\0';
		i++;
	}
	strcpy(final_str,str);
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
