#ifndef SCREEN_HANDLER
#define SCREEN_HANDLER

#include <list>
#include <string>
#include <vector>

#include "SDL.h"

#include "StoredCaptionScreen.h"
#include "DebugText.h"
#include "DemoScreen.h"
#include "Image.h"
#include "InputScreen.h"
#include "KeyboardEntry.h"
#include "MouseHandler.h"
#include "ScreenHandler.h"
#include "SDLUtility.h"
#include "ShortenedText.h"
#include "Subscreen.h"
#include "TextInput.h"
#include "UIMenu.h"

class ScreenHandler {
public:
	enum Screens
	{
		NO_SCREEN = -1,
		PREENTRED_CAPTION_SCREEN,
		MANUAL_CAPTION_SCREEN,
		DEMO_SCREEN
	};

	ScreenHandler();
	~ScreenHandler();
	void ShowScreens(int macro);
private:
	std::vector<Subscreen*> screens_;
	DemoScreen *demoscreen_;
	Subscreen *currentleftscreen_;
	StoredCaptionScreen *storedcaptionscreen_;
	InputScreen *inputscreen_;
	MouseHandler mousefunction_;
	std::vector<Image*> backgroundimages_;
	int backgroundimage_;
	int leftscreen_;
	UIMenu cmenu_;
	UIButton* menubuttonscreens_;
	UIMenu menuscreens_;
};

#endif //SCREEN_HANDLER