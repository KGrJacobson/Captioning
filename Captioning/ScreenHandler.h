#ifndef SCREEN_HANDLER
#define SCREEN_HANDLER

#include <list>
#include <string>

#include "SDL.h"

#include "DebugText.h"
#include "DemoScreen.h"
#include "Image.h"
#include "InputScreen.h"
#include "MouseHandler.h"
#include "ScreenHandler.h"
#include "SDLUtility.h"
#include "Subscreen.h"

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
	std::list<Subscreen*> screens_;
	DemoScreen *demoscreen_;
	InputScreen *inputscreen_;
	bool shift_;
	MouseHandler *mousetoevaluate_;
	MouseHandler *previousmousevent_;
	MouseHandler *currentmouseevent_;
	int mouseevent_;
	bool ismousedown_;
	Image backgroundimage_;
};

#endif //SCREEN_HANDLER