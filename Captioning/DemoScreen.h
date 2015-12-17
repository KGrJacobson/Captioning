#ifndef DEMO_SCREEN
#define DEMO_SCREEN

#include <list>
#include <string>

#include "SDL.h"

#include "CaptionContainer.h"
#include "DebugText.h"
#include "DemoScreenTab.h"
#include "MouseHandler.h"
#include "SDLUtility.h"
#include "Subscreen.h"

static const int ASPECT_RATIO_X = 16;
static const int ASPECT_RATIO_Y = 9;
static const int MAGNIFICATION_MULTIPLIER = 40;

static const int DEMOSCREEN_TAB_HEIGHT = 20;

class DemoScreen : public Subscreen
{
public:
	DemoScreen(int setfontsizeint);
	~DemoScreen();
	void DrawNewCaption();
	MouseHandler *CheckMouseHandlers(int mouseevent);
	SDL_Rect GetScreenSize();
	int Show();
	bool SetCaptionText(std::string text, int captionid);
	std::string GetSelectedCaptionText();
	void CreateCaption(std::string text, double x, double y, double w, int containerid);
	void ClearAllCaptionText();
	void DeleteAllCaptions();
private: 
	int basefontsize_;
	MouseHandler mousefunction_;
	SDL_Rect screenarea_;
	SDL_Rect demoarea_;
	SDL_Rect *drawncaptionarea_;
	CaptionContainer *selectedcaption_;
	DemoScreenTab *currenttab_;
	std::list<CaptionContainer*> captionlist_;
};

#endif //DEMO_SCREEN