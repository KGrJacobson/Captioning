#pragma once
#include <list>
#include <string>
#include "DebugText.h"
#include "SDL.h"
#include "SDLUtility.h"
#include "ScreenHandler.h"
#include "Subscreen.h"
#include "MouseHandler.h"
#include "DemoScreen.h"
#include "InputScreen.h"

class ScreenHandler {
public:
	ScreenHandler();
	~ScreenHandler();
	void PreEventMouseSetup();
	void HandleEvents(const SDL_Event &e);
	void PostEventMouseSetup();
	void ShowScreens();
	int GetCurrentMouseState(int mouseevent, bool isdown);
private:
	std::list<Subscreen*> screens;
	DemoScreen *demoscreen;
	InputScreen *inputscreen;
	bool shift;
	MouseHandler *mousetoevaluate;
	MouseHandler *previousmousevent;
	MouseHandler *currentmouseevent;
	int mouseevent;
	bool ismousedown;
};