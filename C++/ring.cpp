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
char final_str[1024] = "Ring:(";

int main(int argc, char* argv[]) {
	char str[512];
	char* new_str;
	bool skip = 0;
	int i;

	std::string clip = GetClipboardText();
	strcpy(str,clip.c_str());

	if(!strcmp(str,"")) {
		printf("ERROR: Clipboard is empty!\n");
		return -1;
	}

	new_str = strtok(str, " ,{|=\r\n\t{}");
	while(new_str != NULL) {
		if((skip = !skip)) {
			strcat(final_str,new_str);
			strcat(final_str,",");
		}
		new_str = strtok(NULL, " ,{|=\r\n\t{}");
	}
	final_str[strlen(final_str)-1] = ')';
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
