#pragma once
#include "SDL.h"
#include "SDLUtility.h"

class MouseHandler {
public:
	void Init(int x, int y, int w, int h);
	bool IsActive();
	void SetActive(int eventtype);
	void SetMouseArea(int x, int y, int w, int h);
	void ShowMouseArea();
	int GetEvent();
	int GetTicks();
	void ResetMouseEvents();
private:
	int mouseevent;
	bool active;
	int ticks;
	SDL_Rect mousearea;
	SDL_Color color;
};