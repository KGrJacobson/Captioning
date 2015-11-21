#pragma once
#include <string>
#include <list>
#include "SDL.h"
#include "SDLUtility.h"

class CaptionContainer
{
public:
	void Init(std::string text, int x, int y, int w);
	void SetText(std::string text);
	int GetX();
	int GetY();
	int GetW();
	std::string GetText();
	void ShowContainer();
private:
	std::string text;
	int x;
	int y;
	int w;
	SDL_Color color;
}; 