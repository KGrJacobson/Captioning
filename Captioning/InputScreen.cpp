#include <list>
#include <string>

#include "SDL.h"

#include "CaptionContainer.h"
#include "DebugText.h"
#include "InputScreen.h"
#include "MouseHandler.h"
#include "SDLUtility.h"

InputScreen::InputScreen(SDL_Rect setscreenarea)
{
	screenarea_ = setscreenarea;
	texttexture_.Init("meiryo.ttc", 32);
	mousefunction_.Init(screenarea_.x, screenarea_.y, screenarea_.w, screenarea_.h);

	textinputbox_ = SDL_Rect{
		static_cast<int>((screenarea_.w * .5) - ((screenarea_.w * .95) * .5)),
		static_cast<int>((screenarea_.h * .5) - (TEXT_INPUT_BOX_HEIGHT * .5)),
		static_cast<int>(screenarea_.w * .95),
		TEXT_INPUT_BOX_HEIGHT };

	confirmbutton_.Init(
		static_cast<int>(textinputbox_.x + (textinputbox_.w * .01)),
		static_cast<int>(textinputbox_.y + (textinputbox_.h * .95)) - static_cast<int>(textinputbox_.h * .25),
		static_cast<int>(textinputbox_.w * .15),
		static_cast<int>(textinputbox_.h * .25));

	cancelbutton_.Init(
		static_cast<int>(textinputbox_.x + (textinputbox_.w * .02)) + confirmbutton_.GetMouseArea()->w,
		static_cast<int>(textinputbox_.y + (textinputbox_.h * .95)) - static_cast<int>(textinputbox_.h * .25),
		static_cast<int>(textinputbox_.w * .15),
		static_cast<int>(textinputbox_.h * .25));

	textcolor_ = SDL_Color{ 255, 255, 255, 255 };
}

MouseHandler *InputScreen::CheckMouseHandlers(int mouseaction)
{
	MouseHandler *foundhandler = NULL;

	if (SDLUtility::IsMouseActive(&screenarea_))
	{
		if (SDLUtility::IsMouseActive(mousefunction_.GetMouseArea()))
			foundhandler = &mousefunction_;

		if (SDLUtility::IsMouseActive(confirmbutton_.GetMouseArea()))
			foundhandler = &confirmbutton_;

		if (SDLUtility::IsMouseActive(cancelbutton_.GetMouseArea()))
			foundhandler = &cancelbutton_;
	}

	return foundhandler;
}

void InputScreen::Show()
{
	SDL_Color screenbackgroundcolor{ 0, 0, 0, 55 };
	SDL_Color textinputboxcolor{ 77, 77, 77, 255 };

	SDLUtility::CreateSquare(&screenarea_, &screenbackgroundcolor);
	SDLUtility::CreateSquare(&textinputbox_, &textinputboxcolor);

	SDLUtility::PostText(&texttexture_, textinputbox_.x, textinputbox_.y);

	bool confirmnotshown = true;
	bool cancelnotshown = true;

	switch (confirmbutton_.GetEvent())
	{
	case LEFT_BUTTON_DOWN:
		confirmbutton_.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		confirmnotshown = false;
		break;
	case LEFT_BUTTON_UP:
		break;
	}

	switch (cancelbutton_.GetEvent())
	{
	case LEFT_BUTTON_DOWN:
		cancelbutton_.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		cancelnotshown = false;
		break;
	case LEFT_BUTTON_UP:
		break;
	}

	if (confirmnotshown)
		confirmbutton_.ShowMouseArea(SDL_Color{ 0, 170, 0, 255 });

	if (cancelnotshown)
		cancelbutton_.ShowMouseArea(SDL_Color{ 170, 0, 0, 255 });
}

void InputScreen::InsertCharacter(char character, bool isshift)
{
	if (character >= 'a' && character <= 'z' && isshift == true)
	{
		currenttext_ = currenttext_ + static_cast<char>(character - 32);
	}
	else
	{
		currenttext_ = currenttext_ + static_cast<char>(character);
	}

	texttexture_.CreateQuickTextureFromText(currenttext_);
}

void InputScreen::DeleteCharacter()
{
	if (currenttext_ != "")
	{
		currenttext_.pop_back();
		texttexture_.CreateQuickTextureFromText(currenttext_);
	}
}

void InputScreen::KeyboardInput(const SDL_Event &e, bool shift)
{
	switch (e.key.keysym.sym) 
	{
	case SDLK_BACKSPACE:
		DeleteCharacter();
		break;
	case SDLK_SPACE:
		InsertCharacter(' ', shift);
		break;
	case SDLK_PERIOD:
		InsertCharacter('.', shift);
		break;
	case SDLK_a:
		InsertCharacter('a', shift);
		break;
	case SDLK_b:
		InsertCharacter('b', shift);
		break;
	case SDLK_c:
		InsertCharacter('c', shift);
		break;
	case SDLK_d:
		InsertCharacter('d', shift);
		break;
	case SDLK_e:
		InsertCharacter('e', shift);
		break;
	case SDLK_f:
		InsertCharacter('f', shift);
		break;
	case SDLK_g:
		InsertCharacter('g', shift);
		break;
	case SDLK_h:
		InsertCharacter('h', shift);
		break;
	case SDLK_i:
		InsertCharacter('i', shift);
		break;
	case SDLK_j:
		InsertCharacter('j', shift);
		break;
	case SDLK_k:
		InsertCharacter('k', shift);
		break;
	case SDLK_l:
		InsertCharacter('l', shift);
		break;
	case SDLK_m:
		InsertCharacter('m', shift);
		break;
	case SDLK_n:
		InsertCharacter('n', shift);
		break;
	case SDLK_o:
		InsertCharacter('o', shift);
		break;
	case SDLK_p:
		InsertCharacter('p', shift);
		break;
	case SDLK_q:
		InsertCharacter('q', shift);
		break;
	case SDLK_r:
		InsertCharacter('r', shift);
		break;
	case SDLK_s:
		InsertCharacter('s', shift);
		break;
	case SDLK_t:
		InsertCharacter('t', shift);
		break;
	case SDLK_u:
		InsertCharacter('u', shift);
		break;
	case SDLK_v:
		InsertCharacter('v', shift);
		break;
	case SDLK_w:
		InsertCharacter('w', shift);
		break;
	case SDLK_x:
		InsertCharacter('x', shift);
		break;
	case SDLK_y:
		InsertCharacter('y', shift);
		break;
	case SDLK_z:
		InsertCharacter('z', shift);
		break;
	}
}

std::string InputScreen::PostText()
{
	std::string texttoreturn = currenttext_;
	currenttext_ = "";
	texttexture_.DestroyTexture();

	return texttoreturn;
}
