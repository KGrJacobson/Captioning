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
	void Init(std::string initialtext, float initialx, float initialy, float initialw, int destinationw, int initialfontsize, int id);
	void SetText(std::string newtext, int destinationw);
	void EraseText();
	int GetID();
	std::string GetText();
	void ShowContainer(SDL_Rect destrect);
	void ShowCaption(SDL_Rect destrect);
	void FitText(std::string texttofit, float destinationw);
private:
	std::string text;
	float x, y, w;
	int fontsize;
	int id;
	SDL_Color color;
	std::list<TextInput*> texttextures;
}; 