#ifndef SCREEN_HANDLER
#define SCREEN_HANDLER

#include <list>
#include <string>
#include <vector>

#include "SDL.h"

#include "StoredCaptionScreen.h"
#include "KWindow\DebugText.h"
#include "DemoScreen.h"
#include "KWindow\Image.h"
#include "InputScreen.h"
#include "KWindow\KeyboardEntry.h"
#include "KWindow\MouseHandler.h"
#include "ScreenHandler.h"
#include "KWindow\SDLUtility.h"
#include "KWindow\ShortenedText.h"
#include "KWindow\Subscreen.h"
#include "KWindow\TextInput.h"
#include "KWindow\UIMenu.h"

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