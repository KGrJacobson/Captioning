#include "TextInput.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <string>
#include "SDLUtility.h"

TextInput::TextInput(int textsize)
{
	font = TTF_OpenFont("meiryo.ttc", textsize);

	if (font == NULL)
		printf("Failed to load font SDL_ttf Error: %s\n", TTF_GetError());
}

TextInput::~TextInput()
{
	TTF_CloseFont(font);
	font = NULL;
}

void TextInput::CreateTextureFromText(std::string text)
{
	SDL_Surface *textsurface = TTF_RenderText_Shaded(font, text.c_str(), SDL_Color{ 0, 0, 0, 255 }, SDL_Color{ 255, 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), textsurface);

	imageheight = textsurface->h;
	imagewidth = textsurface->w;

	SDL_FreeSurface(textsurface);
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