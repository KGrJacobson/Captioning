#pragma once
#include "SDL.h"
#include <SDL_ttf.h>
#include <string>

class TextInput
{
public:
	TextInput(int textsize);
	~TextInput();
	void CreateTextureFromText(std::string text);
	SDL_Texture *GetTexture();
	int GetWidth();
	int GetHeight();
	void DestroyTexture();
private:
	SDL_Texture *texture;
	TTF_Font *font;
	int imagewidth;
	int imageheight;
};