#include <algorithm>
#include <list>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "SDLUtility.h"
#include "TextInput.h"
#include "UIElements.h"

TextInput::TextInput()
{
	texture_ = NULL;
	font_ = NULL;
	currenttext_ = "";
	currentunicodetext_ = L"";
	isfinal_ = false;
}

TextInput::~TextInput()
{
	DestroyTexture();
	TTF_CloseFont(font_);
	font_ = NULL;
}

int TextInput::Init(std::string ttffilepath, int fontsize)
{
	DestroyTexture();

	font_ = TTF_OpenFont(ttffilepath.c_str(), fontsize);
	if (font_ == NULL)
	{
		printf("Failed to load font SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}

	return 0;
}

void TextInput::CreateTextureFromText(std::string text)
{
	if (text == "")
	{
		DestroyTexture();
	}
	else
	{
		if (currenttext_ != text)
		{
			SDL_Surface *textsurface;

			textsurface = TTF_RenderText_Blended(font_, text.c_str(), UIElements::GetUIElementColor(UIElements::TEXT_COLOR, UIElements::SOLID_COLOR));
			texture_ = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), textsurface);

			imageheight_ = textsurface->h;
			imagewidth_ = textsurface->w;

			SDL_FreeSurface(textsurface);
			currenttext_ = text;
		}
	}

	isfinal_ = true;
}

void TextInput::CreateTextureFromText(std::wstring text)
{
	if (text == L"")
	{
		DestroyTexture();
	}
	else
	{
		if (currentunicodetext_ != text)
		{
			SDL_Surface *textsurface;
			
			SDL_Surface *currentcharsurface;
			std::list<SDL_Surface*> charsurfacelist;
			int textwidth = 0;
			
			for (std::wstring::iterator it = text.begin(); it != text.end(); ++it)
			{
				currentcharsurface = TTF_RenderGlyph_Solid(font_, (*it), UIElements::GetUIElementColor(UIElements::TEXT_COLOR, UIElements::SOLID_COLOR));
				charsurfacelist.push_back(currentcharsurface);
				textwidth = textwidth + currentcharsurface->w;
			}

			textsurface = SDL_CreateRGBSurface(0, textwidth, TextHeight(), 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

			SDL_Rect nextposition;
			int nextxposition = 0;
			for (std::list<SDL_Surface*>::iterator it = charsurfacelist.begin(); it != charsurfacelist.end(); ++it)
			{
				nextposition = SDL_Rect{ nextxposition, 0, (*it)->w, (*it)->h };
				SDL_BlitSurface((*it), NULL, textsurface, &nextposition);
				nextxposition = nextxposition + (*it)->w;
				SDL_FreeSurface((*it));
			}

			texture_ = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), textsurface);

			imageheight_ = textsurface->h;
			imagewidth_ = textsurface->w;

			SDL_FreeSurface(textsurface);
			charsurfacelist.clear();
			currentunicodetext_ = text;
		}
	}

	isfinal_ = true;
}

void TextInput::CreateQuickTextureFromText(std::string text)
{
	if (text == "")
	{
		DestroyTexture();
	}
	else
	{
		if (currenttext_ != text)
		{
			SDL_Surface *textsurface;

			textsurface = TTF_RenderText_Solid(font_, text.c_str(), UIElements::GetUIElementColor(UIElements::TEXT_COLOR, UIElements::SOLID_COLOR));
			texture_ = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), textsurface);

			imageheight_ = textsurface->h;
			imagewidth_ = textsurface->w;

			SDL_FreeSurface(textsurface);
			currenttext_ = text;
		}
	}

	isfinal_ = false;
}

SDL_Texture *TextInput::GetTexture()
{
	return texture_;
}

int TextInput::GetWidth()
{
	return imagewidth_;
}

int TextInput::GetHeight()
{
	return imageheight_;
}

std::string TextInput::GetCurrentText()
{
	return currenttext_;
}

std::wstring TextInput::GetCurrentUnicodeText()
{
	return currentunicodetext_;
}

bool TextInput::GetFinal()
{
	return isfinal_;
}

void TextInput::DestroyTexture()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		imagewidth_ = 0;
		imageheight_ = 0;
		currenttext_ = "";
		currentunicodetext_ = L"";
	}
}

int TextInput::TextWidth(std::string text)
{
	int widthoftext;
	TTF_SizeText(font_, text.c_str(), &widthoftext, NULL);

	return widthoftext;
}

int TextInput::TextHeight()
{
	return TTF_FontHeight(font_);
}

