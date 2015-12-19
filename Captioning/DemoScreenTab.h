#ifndef DEMO_SCREEN_TAB
#define DEMO_SCREEN_TAB

#include "SDL.h"

#include "CaptionContainer.h"
#include "MouseHandler.h"
#include "UIButton.h"

class DemoScreenTab {
public:
	enum Demo_Screen_Tab_Return_Values 
	{
		NO_VALUE,
		CLOSE_TAB,
		OPEN_TAB
	};

	DemoScreenTab();
	~DemoScreenTab();
	MouseHandler *CheckMouseEvents();
	int ShowTab();
	void SetTabArea(SDL_Rect newarea);
	std::list<CaptionContainer*> *GetCaptions();
private:
	std::list<CaptionContainer*> *captionlist_;
	SDL_Rect tabarea_;
	UIButton tabbutton;
};

#endif //DEMO_SCREEN_TAB