#include <string>

#include "SDL.h"

#include "MouseHandler.h"
#include "SDLUtility.h"
#include "TextInput.h"
#include "UIButton.h"
#include "UIElements.h"

UIButton::UIButton(RelativeRect relativerect, SDL_Rect destrect, std::string text, bool istextcentered)
{
	relativecoordinatesrect_ = relativerect;
	absolutecoordinatesrect_ = SDLUtility::GetAbsoluteRect(relativecoordinatesrect_, destrect);
	buttontext_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);
	buttontext_.CreateTextureFromText(text);
	centertext_ = istextcentered;
	donotresetarea_ = false;
	mousefunction_.Init(absolutecoordinatesrect_);
}

UIButton::UIButton(SDL_Rect buttonarea, std::string text, bool istextcentered)
{
	relativecoordinatesrect_ = RelativeRect{ 0.0, 0.0, 0.0, 0.0 };
	absolutecoordinatesrect_ = buttonarea;
	buttontext_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);
	buttontext_.CreateTextureFromText(text);
	centertext_ = istextcentered;
	donotresetarea_ = true;
	mousefunction_.Init(absolutecoordinatesrect_);
}

UIButton::~UIButton()
{
}

MouseHandler *UIButton::CheckMouseHandler()
{
	if (SDLUtility::IsMouseActive(mousefunction_.GetMouseArea()))
		return &mousefunction_;
	
	return NULL;
}

int UIButton::GetMouseEvent()
{
	return mousefunction_.GetEvent();
}

SDL_Rect UIButton::GetButtonArea()
{
	return absolutecoordinatesrect_;
}

TextInput *UIButton::GetText()
{
	return &buttontext_;
}

bool UIButton::IsTextCentered()
{
	return centertext_;
}

void UIButton::SetButtonArea(SDL_Rect destrect)
{
	if (donotresetarea_ != true)
	{
		absolutecoordinatesrect_ = SDLUtility::GetAbsoluteRect(relativecoordinatesrect_, destrect);
	}
}

void UIButton::SetButtonCoordinates(int x, int y)
{
	absolutecoordinatesrect_.x = x;
	absolutecoordinatesrect_.y = y;

	SDL_Rect mouserect = mousefunction_.GetMouseArea();
	mousefunction_.SetMouseArea(SDL_Rect{ x, y, mouserect.w, mouserect.h });
}
