#define _WIN32_WINNT 0x0500
#include <iostream>
#include <Windows.h>
#include <string>
#include "wtypes.h"
#include <math.h>

  void GetDesktopResolution(int& horizontal, int& vertical);
  void RightClick();
  void LeftClick();
  extern "C" void gotoxy(int x, int y);
  //void gotoxy(int x,int y);

using namespace std;
int WINAPI WinMain ( HINSTANCE hInst, HINSTANCE P, LPSTR CMD, int nShowCmd ) {
	int hor = 0;
	int ver = 0;
  int radius = 50;
  unsigned int step = 0;

  /* 2 Seconds till start */
  Sleep(2000);

	GetDesktopResolution(hor,ver);
  hor /= 2;
  ver /= 2;

 // gotoxy(hor, ver);

	/* Set cursor into the middle of the screen */
	SetCursorPos(hor,ver);

	while(1) {
    if(GetAsyncKeyState(VK_CONTROL) && GetKeyState(VK_OEM_6)) {
      return 1;
    }

    SetCursorPos(hor + radius*cos(step),ver + radius*sin(step));
		Sleep(20);
    step++;
    LeftClick();
		//RightClick();
	}
}

void GetDesktopResolution(int& horizontal, int& vertical) {
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

void RightClick() {  
  INPUT Input={0};
  Input.type = INPUT_MOUSE;
  Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
  SendInput(1,&Input,sizeof(INPUT));

  ZeroMemory(&Input,sizeof(INPUT));
  Input.type = INPUT_MOUSE;
  Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
  SendInput(1,&Input,sizeof(INPUT));
}

void LeftClick() {  
  INPUT Input={0};
  Input.type = INPUT_MOUSE;
  Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  SendInput(1,&Input,sizeof(INPUT));

  ZeroMemory(&Input,sizeof(INPUT));
  Input.type = INPUT_MOUSE;
  Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
  SendInput(1,&Input,sizeof(INPUT));
}




