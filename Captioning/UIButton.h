#ifndef UI_BUTTON
#define UI_BUTTON

#include <string>

#include "SDL.h"

#include "MouseHandler.h"
#include "SDLUtility.h"
#include "TextInput.h"

class UIButton 
{
public:
	UIButton(RelativeRect relativerect, SDL_Rect destrect, std::string text, bool istextcentered);
	UIButton(SDL_Rect buttonarea, std::string text, bool istextcentered);
	~UIButton();
	MouseHandler *CheckMouseHandler();
	int GetMouseEvent();
	SDL_Rect GetButtonArea();
	TextInput *GetText();
	bool IsTextCentered();
	void SetButtonArea(SDL_Rect destrect);
	void SetButtonCoordinates(int x, int y);
private:
	RelativeRect relativecoordinatesrect_;
	SDL_Rect absolutecoordinatesrect_;
	TextInput buttontext_;
	MouseHandler mousefunction_;
	bool centertext_;
	bool donotresetarea_;
};

#endif //UI_BUTTON