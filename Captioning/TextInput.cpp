#include "TextInput.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "SDLUtility.h"
#include <iostream>
#include <algorithm>

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

void TextInput::CreateTextureFromText(std::string text, bool isunicode)
{
	if (text != currenttext) 
	{
		SDL_Surface *textsurface;

		if (!isunicode) 
		{
			textsurface = TTF_RenderText_Blended(font, text.c_str(), SDL_Color{ 255, 255, 255, 255 });
			texture = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), textsurface);
		}
		else
		{
			textsurface = TTF_RenderText_Blended(font, text.c_str(), SDL_Color{ 255, 255, 255, 255 });
			//textsurface = TTF_RenderGlyph_Solid(font, 12355, SDL_Color{ 255, 255, 255, 255 });
			texture = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), textsurface);
		}

		imageheight = textsurface->h;
		imagewidth = textsurface->w;

		SDL_FreeSurface(textsurface);
		currenttext = text;
	}
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

int TextInput::TextWidth(std::string text)
{
	int widthoftext;
	TTF_SizeText(font, text.c_str(), &widthoftext, NULL);

	return widthoftext;
}

