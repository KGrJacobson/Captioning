#pragma once
#include "Image.h"
#include <string>
#include <list>
#include "SDL.h"
#include "CaptionContainer.h"
#include "Subscreen.h"
#include "MouseHandler.h"
#include "TextInput.h"

static const int TEXT_INPUT_BOX_HEIGHT = 100;

class InputScreen : public Subscreen
{
public:
	InputScreen(SDL_Rect setscreenarea);
	MouseHandler *CheckMouseHandlers(int mouseaction);
	void Show();
	void InsertCharacter(char character, bool isshift);
	void DeleteCharacter();
	void KeyboardInput(SDL_Event *e, bool shift);
	std::string PostText();
private:
	SDL_Rect screenarea;
	SDL_Rect textinputbox;
	TextInput texttexture;
	MouseHandler mousefunction;
	MouseHandler confirmbutton;
	MouseHandler cancelbutton;
	std::string currenttext;
	SDL_Color textcolor;
};