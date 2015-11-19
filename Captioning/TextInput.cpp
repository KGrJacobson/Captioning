#include "TextInput.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <string>
#include "SDLUtility.h"
#include <iostream>

TextInput::TextInput()
{
	texture = NULL;
	font = NULL;
	currenttext = "";
}

TextInput::~TextInput()
{
	DestroyTexture();
	TTF_CloseFont(font);
	font = NULL;
	currenttext = "";
}

int TextInput::Init(std::string ttffilepath, int fontsize)
{
	DestroyTexture();

	font = TTF_OpenFont(ttffilepath.c_str(), fontsize);
	if (font == NULL)
	{
		printf("Failed to load font SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}

	return 0;
}

void TextInput::CreateTextureFromText(std::string text, int x, int y)
{
	if (text != currenttext) {
		SDL_Surface *textsurface = TTF_RenderText_Shaded(font, text.c_str(), SDL_Color{ 255, 255, 255, 255 }, SDL_Color{ 0, 0, 0, 255 });
		texture = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), textsurface);

		imageheight = textsurface->h;
		imagewidth = textsurface->w;

		SDL_FreeSurface(textsurface);
		currenttext = text;
	}

	SDLUtility::PostText(this, x, y);
}

SDL_Texture *TextInput::GetTexture()
{
	return texture;
}

int TextInput::GetWidth()
{
	return imagewidth;
}

int TextInput::GetHeight()
{
	return imageheight;
}

void TextInput::DestroyTexture()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		imagewidth = 0;
		imageheight = 0;
	}
}