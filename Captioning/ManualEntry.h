#pragma once
#include "Image.h"
#include <string>
#include <list>
#include "SDL.h"
#include "CaptionContainer.h"

class ManualEntry
{
public:
	ManualEntry();
	void InsertCharacter(char character, bool isshift);
	void DeleteCharacter();
	int TranslateCharacter(char character);
	void PostCurrentEntry(int x, int y);
	std::string CreateString();
	void KeyboardInput(SDL_Event *e, bool shift);
private:
	Image charimage;
	std::list<char> textentry;
	SDL_Color textcolor;
};