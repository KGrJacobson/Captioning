#pragma once
#include "SDL.h"
#include <SDL_ttf.h>
#include <string>

class TextInput
{
public:
	TextInput();
	~TextInput();
	int Init(std::string ttffilepath, int fontsize);
	void CreateTextureFromText(std::string text, bool isunicode);
	SDL_Texture *GetTexture();
	int GetWidth();
	int GetHeight();
	void DestroyTexture();
	int TextWidth(std::string text);
private:
	SDL_Texture *texture;
	TTF_Font *font;
	std::string currenttext;
	int imagewidth;
	int imageheight;
};