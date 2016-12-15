#pragma once
#include <windows.h>
#include <iostream>

/* Open a window of the correct size for the game.*/
class WindowController
{
public:
	static void InitializeWindow(int width, int height);
	static void DestroyWindow();
	static WindowController* windowInstance;
	HANDLE hConOut;
	static int window_width;
	static int window_height;
private:
	WindowController(int width, int height);
	~WindowController();
	SMALL_RECT r;
	COORD c;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
};

