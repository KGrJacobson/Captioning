#pragma once
#include <string>
#include <list>
#include "SDL.h"
#include "SDLUtility.h"
#include "TextInput.h"

class CaptionContainer
{
public:
	~CaptionContainer();
	void Init(std::string initialtext, int initialx, int initialy, int initialw);
	void SetText(std::string newtext);
	void EraseText();
	int GetX();
	int GetY();
	int GetW();
	std::string GetText();
	void ShowContainer();
	void ShowCaption();
	void FitText(std::string texttofit);
private:
	std::string text;
	int x;
	int y;
	int w;
	SDL_Color color;
	std::list<TextInput*> texttextures;
}; 