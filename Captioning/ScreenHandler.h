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

//The "core" of the program, the ScreenHandler is the go-between for subscreens interacting with each other.
//The ScreenHandler is responsible for calling the Show functions for each subscreen and processing the 
//return codes the screens return.  The class also handles universal program UI elements like the menu bar,
//non-specific context menu, and the programs background image.
class ScreenHandler {
public:
	//The possible subscreens the program can contain.
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
	UIMenu *cmenu_;
	UIButton *menubuttonscreens_;
	UIMenu *menuscreens_;

	int captionindex_;
	UIButton *menubuttonfiles_;
	UIMenu *menufiles_;
	std::vector<std::string> captionfiles_;
};

#endif //SCREEN_HANDLER