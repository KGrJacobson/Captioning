#ifndef DEMO_SCREEN
#define DEMO_SCREEN

#include <list>
#include <string>
#include <vector>

#include "SDL.h"

#include "CaptionContainer.h"
#include "KWindow\UIMenu.h"
#include "KWindow\DebugText.h"
#include "KWindow\MouseHandler.h"
#include "KWindow\SDLUtility.h"
#include "KWindow\Subscreen.h"
#include "KWindow\UITab.h"

static const int ASPECT_RATIO_X = 16;
static const int ASPECT_RATIO_Y = 9;
static const int MAGNIFICATION_MULTIPLIER = 40;

static const int DEMOSCREEN_TAB_HEIGHT = 20;

//The Demo Screen, along with the left screen and the template screen, is one of the main subscreens of the captioning system.
//The Demo Screen represents a simulation of the OBS stream that the captions will be sent to.  The size of the screen is 
//dependent on the ASPECT_RATIO const numbers delcared in the DemoScreen header file and default to 16:9, the resolution Twitch
//uses for streaming.  The actual size of the screen is dependent on the MAGNIFICATION_MULTIPLIER number, at default the screen 
//is exactly 16 : 9 pixels, but is multiplied by the multiplier to become a reasonable size (default: 40 times the base pixels).
//Handled in the screen are tabs to simulate multiple Demo Screens and a list of Caption Containers that represent the actual 
//captions to send to OBS.  Only the current active tab will have the content of its containers sent to OBS.  Aside from being the 
//destination of captions selected from files, it is also possible to draw new containers via clicking and dragging on the screen.
//Any containers created this way are not saved and only exist for the current instance of the program.
class DemoScreen : public Subscreen
{
public:
	enum Demo_Screen_Return_Code
	{
		NO_RETURN_CODE,
	};

	enum Tab_Context_Menu_Code
	{
		RENAME_TAB
	};

	DemoScreen(int setfontsizeint);
	~DemoScreen();
	void DrawNewCaption();
	SDL_Rect GetScreenSize();
	int Show();
	bool SetCaptionText(std::string text, int captionid);
	std::string GetSelectedCaptionText();
	void CreateCaption(std::string text, double x, double y, double w, int containerid);
	void ClearAllCaptionText();
	void DeleteAllCaptions();
	UIMenu *CreateNewTabContextMenu();
	void CreateNewTab();
private: 
	int basefontsize_;
	MouseHandler mousefunction_;
	SDL_Rect screenarea_;
	SDL_Rect demoarea_;
	SDL_Rect *drawncaptionarea_;
	CaptionContainer *selectedcaption_;
	std::vector<std::list<CaptionContainer*>*> captionlist_;
	std::vector<UITab*> tablist_;
	int currenttab_;
	UIButton *newtabbutton_;
};

#endif //DEMO_SCREEN