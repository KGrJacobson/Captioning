#ifndef SCREEN_HANDLER
#define SCREEN_HANDLER

#include <list>
#include <string>
#include <vector>

#include "SDL.h"

#include "ContextMenu.h"
#include "DebugText.h"
#include "DemoScreen.h"
#include "Image.h"
#include "InputScreen.h"
#include "KeyboardEntry.h"
#include "MouseHandler.h"
#include "ScreenHandler.h"
#include "SDLUtility.h"
#include "Subscreen.h"
#include "TextInput.h"

class ScreenHandler {
public:
	ScreenHandler();
	~ScreenHandler();
	void PreEventMouseSetup();
	void HandleEvents(const SDL_Event &e);
	void PostEventMouseSetup();
	void ShowScreens();
	int GetCurrentMouseState(int mouseevent, bool isdown);
	void SetEntryTexture(TextInput *textinput);
	void SetContextMenu(ContextMenu *contextmenu);
private:
	std::list<Subscreen*> screens_;
	DemoScreen *demoscreen_;
	InputScreen *inputscreen_;
	KeyboardEntry keyboardentry_;
	ContextMenu *currentcontextmenu_;
	MouseHandler *mousetoevaluate_;
	MouseHandler *previousmousevent_;
	MouseHandler *currentmouseevent_;
	MouseHandler mousefunction_;
	int mouseevent_;
	bool ismousedown_;
	std::vector<Image*> backgroundimages_;
	int backgroundimage_;
	ContextMenu cmenu_;
};

#endif //SCREEN_HANDLER