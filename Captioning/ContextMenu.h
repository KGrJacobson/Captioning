#ifndef CONTEXT_MENU
#define CONTEXT_MENU

#include <vector>

#include "SDL.h"

#include "MouseHandler.h"
#include "UIButton.h"

class ContextMenu
{
public:
	static const int STANDARD_CONTEXT_MENU_HEIGHT = 20;
	static const int STANDARD_CONTEXT_MENU_WIDTH = 200;
	static const int STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN = 17;
	static const int NO_CONTEXT_MENU_BUTTONS_PRESSED = -1;

	ContextMenu();
	~ContextMenu();
	int GetButtonPress();
	void ResetMenu();
	void AddListItem(UIButton *newitem);
	void SetXY(int x, int y);
	void ShowMenu();
	SDL_Rect GetMenuArea();
private:
	SDL_Rect menuarea_;
	std::vector<UIButton*> optionlist_;
	int buttonpressed_;
};

#endif //CONTEXT_MENU