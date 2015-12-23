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
	void ShowScreens(int macro);
private:
	std::list<Subscreen*> screens_;
	DemoScreen *demoscreen_;
	InputScreen *inputscreen_;
	MouseHandler mousefunction_;
	std::vector<Image*> backgroundimages_;
	int backgroundimage_;
	ContextMenu cmenu_;
};

#endif //SCREEN_HANDLER