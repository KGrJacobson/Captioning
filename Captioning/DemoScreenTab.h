#ifndef DEMO_SCREEN_TAB
#define DEMO_SCREEN_TAB

#include "CaptionContainer.h"
#include "MouseHandler.h"

class DemoScreenTab {
public:
	void ShowTab();
	void SetTabArea(SDL_Rect newarea);
private:
	std::list<CaptionContainer*> captionlist_;
	SDL_Rect tabarea_;
	MouseHandler buttonarea_;
};

#endif //DEMO_SCREEN_TAB