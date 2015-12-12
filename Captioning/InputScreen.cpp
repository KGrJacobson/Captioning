#include "InputScreen.h"
#include "Image.h"
#include "SDLUtility.h"
#include <string>
#include <list>
#include <iostream>
#include "SDL.h"
#include "DebugText.h"
#include "CaptionContainer.h"
#include "MouseHandler.h"

InputScreen::InputScreen(SDL_Rect setscreenarea)
{
	screenarea = setscreenarea;
	texttexture.Init("meiryo.ttc", 32);
	mousefunction.Init(screenarea.x, screenarea.y, screenarea.w, screenarea.h);

	textinputbox = SDL_Rect{
		static_cast<int>((screenarea.w * .5) - ((screenarea.w * .95) * .5)),
		static_cast<int>((screenarea.h * .5) - (TEXT_INPUT_BOX_HEIGHT * .5)),
		static_cast<int>(screenarea.w * .95),
		TEXT_INPUT_BOX_HEIGHT };

	confirmbutton.Init(
		static_cast<int>(textinputbox.x + (textinputbox.w * .01)),
		static_cast<int>(textinputbox.y + (textinputbox.h * .95)) - static_cast<int>(textinputbox.h * .25),
		static_cast<int>(textinputbox.w * .15),
		static_cast<int>(textinputbox.h * .25));

	cancelbutton.Init(
		static_cast<int>(textinputbox.x + (textinputbox.w * .02)) + confirmbutton.GetMouseArea()->w,
		static_cast<int>(textinputbox.y + (textinputbox.h * .95)) - static_cast<int>(textinputbox.h * .25),
		static_cast<int>(textinputbox.w * .15),
		static_cast<int>(textinputbox.h * .25));

	textcolor = SDL_Color{ 255, 255, 255, 255 };
}

MouseHandler *InputScreen::CheckMouseHandlers(int mouseaction)
{
	MouseHandler *foundhandler = NULL;

	if (SDLUtility::IsMouseActive(&screenarea))
	{
		if (SDLUtility::IsMouseActive(mousefunction.GetMouseArea()))
			foundhandler = &mousefunction;

		if (SDLUtility::IsMouseActive(confirmbutton.GetMouseArea()))
			foundhandler = &confirmbutton;

		if (SDLUtility::IsMouseActive(cancelbutton.GetMouseArea()))
			foundhandler = &cancelbutton;
	}

	return foundhandler;
}

void InputScreen::Show()
{
	SDL_Color screenbackgroundcolor{ 0, 0, 0, 55 };
	SDL_Color textinputboxcolor{ 77, 77, 77, 255 };

	SDLUtility::CreateSquare(&screenarea, &screenbackgroundcolor);
	SDLUtility::CreateSquare(&textinputbox, &textinputboxcolor);

	SDLUtility::PostText(&texttexture, textinputbox.x, textinputbox.y);

	bool confirmnotshown = true;
	bool cancelnotshown = true;

	switch (confirmbutton.GetEvent())
	{
	case LEFT_BUTTON_DOWN:
		confirmbutton.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		confirmnotshown = false;
		break;
	case LEFT_BUTTON_UP:
		break;
	}

	switch (cancelbutton.GetEvent())
	{
	case LEFT_BUTTON_DOWN:
		cancelbutton.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		cancelnotshown = false;
		break;
	case LEFT_BUTTON_UP:
		break;
	}

	if (confirmnotshown)
		confirmbutton.ShowMouseArea(SDL_Color{ 0, 170, 0, 255 });

	if (cancelnotshown)
		cancelbutton.ShowMouseArea(SDL_Color{ 170, 0, 0, 255 });
}

void InputScreen::InsertCharacter(char character, bool isshift)
{
	if (character >= 'a' && character <= 'z' && isshift == true)
	{
		currenttext = currenttext + static_cast<char>(character - 32);
	}
	else
	{
		currenttext = currenttext + static_cast<char>(character);
	}

	texttexture.CreateQuickTextureFromText(currenttext);
}

void InputScreen::DeleteCharacter()
{
	if (currenttext != "")
	{
		currenttext.pop_back();
		texttexture.CreateQuickTextureFromText(currenttext);
	}
}

void InputScreen::KeyboardInput(SDL_Event *e, bool shift)
{
	switch (e->key.keysym.sym) 
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
	std::string texttoreturn = currenttext;
	currenttext = "";
	texttexture.DestroyTexture();

	return texttoreturn;
}
