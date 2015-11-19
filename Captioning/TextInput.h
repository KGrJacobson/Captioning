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
	void CreateTextureFromText(std::string text, int x, int y);
	SDL_Texture *GetTexture();
	int GetWidth();
	int GetHeight();
	void DestroyTexture();
private:
	SDL_Texture *texture;
	TTF_Font *font;
	std::string currenttext;
	int imagewidth;
	int imageheight;
};