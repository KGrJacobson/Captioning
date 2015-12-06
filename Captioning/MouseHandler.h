#pragma once
#include "SDL.h"
#include "SDLUtility.h"
#include "DebugText.h"

enum mousestate
{
	NO_MOUSE_STATE = -1,
	MOUSEOVER,
	LEFT_BUTTON_DOWN,
	LEFT_BUTTON_UP,
	RIGHT_BUTTON_DOWN,
	RIGHT_BUTTON_UP
};

class MouseHandler {
public:
	void Init(int x, int y, int w, int h);
	bool IsActive();
	void SetActive(int eventtype, bool iscurrentdown);
	void SetMouseArea(int x, int y, int w, int h);
	void ShowMouseArea(SDL_Color setcolor);
	int GetCurrentState();
	int GetTicks();
	void ResetMouseEvents();
private:
	int mouseevent;
	bool isactive;
	bool isdown;
	int ticks;
	SDL_Rect mousearea;
};