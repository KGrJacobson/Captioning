#include <list>
#include <string>

#include "SDL.h"

#include "CaptionContainer.h"
#include "KWindow\DebugText.h"
#include "KWindow\InputHandler.h"
#include "InputScreen.h"
#include "KWindow\MouseHandler.h"
#include "ScreenHandler.h"
#include "KWindow\SDLUtility.h"
#include "KWindow\UIButton.h"
#include "KWindow\UIElements.h"

//Initialize input handlers and create the area for each element of the screen.
//setscreenarea is the area of the subscreen.
InputScreen::InputScreen(SDL_Rect setscreenarea)
{
	screenarea_ = setscreenarea;
	texttexture_.Init(32);

	SDL_Rect textinputboxrect = SDL_Rect{
		static_cast<int>((screenarea_.w * .5) - ((screenarea_.w * .95) * .5)),
		static_cast<int>((screenarea_.h * .5) - (TEXT_INPUT_BOX_HEIGHT * .5)),
		static_cast<int>(screenarea_.w * .95),
		TEXT_INPUT_BOX_HEIGHT };

	textinputbox_.Init(textinputboxrect);
	InputHandler::AddMouseHandler(&textinputbox_);

	confirmbutton_ = new UIButton(SDL_Rect{
		static_cast<int>(textinputboxrect.x + (textinputboxrect.w * .01)),
		static_cast<int>(textinputboxrect.y + (textinputboxrect.h * .95)) - static_cast<int>(textinputboxrect.h * .25),
		static_cast<int>(textinputboxrect.w * .15),
		static_cast<int>(textinputboxrect.h * .25) },
		"Apply",
		UIElements::STANDARD_UI_FONT_SIZE,
		false);

	cancelbutton_ = new UIButton(SDL_Rect{
		static_cast<int>(textinputboxrect.x + (textinputboxrect.w * .02)) + confirmbutton_->GetButtonArea().w,
		static_cast<int>(textinputboxrect.y + (textinputboxrect.h * .95)) - static_cast<int>(textinputboxrect.h * .25),
		static_cast<int>(textinputboxrect.w * .15),
		static_cast<int>(textinputboxrect.h * .25) },
		"Cancel",
		UIElements::STANDARD_UI_FONT_SIZE,
		false);
}

InputScreen::~InputScreen()
{
	InputHandler::RemoveMouseHandler(&textinputbox_);

	delete confirmbutton_;
	confirmbutton_ = NULL;
	delete cancelbutton_;
	cancelbutton_ = NULL;
}

//Render subscreen elements and return an enum flag if necessary.
int InputScreen::Show()
{
	int returnflag = NO_RETURN_EVENT;

	SDLUtility::CreateSquare(screenarea_, UIElements::GetUIElementColor(UIElements::INPUT_SCREEN_COLOR, UIElements::TRANSPARENT_COLOR));
	SDLUtility::CreateSquare(textinputbox_.GetMouseArea(), UIElements::GetUIElementColor(UIElements::TEXT_INPUT_BOX, UIElements::SOLID_COLOR));

	SDLUtility::PostText(&texttexture_, textinputbox_.GetMouseArea().x + 3, textinputbox_.GetMouseArea().y + 3);

	switch (textinputbox_.GetEvent())
	{
	case LEFT_BUTTON_UP:
		returnflag = SET_KEYBOARD_ENTRY;
		break;
	}

	switch (confirmbutton_->GetMouseEvent())
	{
	case LEFT_BUTTON_UP:
		returnflag = APPLY_BUTTON_PRESSED;
		break;
	}

	if (texttexture_.GetFinal() == true)
	{
		returnflag = RETURN_KEY_PRESSED;
	}

	switch (cancelbutton_->GetMouseEvent())
	{
	case LEFT_BUTTON_UP:
		returnflag = CLOSE_SCREEN;
		break;
	}

	UIElements::ShowUIButton(confirmbutton_);
	UIElements::ShowUIButton(cancelbutton_);

	return returnflag;
}

//Clear the text texture and return its text.  The major use of this function is to create a caption
//on the Demo Screen with the text returned.
std::string InputScreen::PostCurrentString()
{
	std::string currenttext = texttexture_.GetCurrentText();
	texttexture_.DestroyTexture();

	return currenttext;
}

TextInput *InputScreen::GetTexture()
{
	return &texttexture_;
}

//Return the destination rectangle of the text texture.
SDL_Rect InputScreen::GetTextArea()
{
	return SDL_Rect{ textinputbox_.GetMouseArea().x + 3, textinputbox_.GetMouseArea().y + 3, texttexture_.GetWidth(), texttexture_.GetHeight() };
}
