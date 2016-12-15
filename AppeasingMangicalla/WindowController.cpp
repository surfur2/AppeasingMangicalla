/*
	Much of this code was provided by the source below. Only minute modifications were made.
	Reference: http://www.cplusplus.com/forum/beginner/1481/
*/
#include "WindowController.h"
#include <string>

using namespace std;

WindowController* WindowController::windowInstance = nullptr;

WindowController::WindowController(int height, int width)
{
	hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!GetConsoleScreenBufferInfo(hConOut, &csbi))
		throw runtime_error("You must be attached to a human.");

	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;

	c.X = width;
	c.Y = height;

	string size = "mode ";
	size = size + to_string(width) + "," + to_string(height);
	system(size.c_str());

}


WindowController::~WindowController()
{
}

void WindowController::InitializeWindow(int width, int height)
{
	if (windowInstance == nullptr)
	{
		window_width = width;
		window_height = height;

		windowInstance = new WindowController(width, height);
		
		SetConsoleWindowInfo(windowInstance->hConOut, TRUE, &(windowInstance->r));

		SetConsoleScreenBufferSize(windowInstance->hConOut, windowInstance->c);
	}
}

void WindowController::DestroyWindow()
{
	SetConsoleTextAttribute(windowInstance->hConOut, windowInstance->csbi.wAttributes);
	SetConsoleScreenBufferSize(windowInstance->hConOut, windowInstance->csbi.dwSize);
	SetConsoleWindowInfo(windowInstance->hConOut, TRUE, &(windowInstance->csbi.srWindow));
	delete windowInstance;
	windowInstance = nullptr;
}

int WindowController::window_width;
int WindowController::window_height;


