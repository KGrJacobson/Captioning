#include "Image.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "SDLUtility.h"
#include <iostream>

Image::Image()
{
}

Image::~Image()
{
	DestroyTexture();
}

int Image::CreateTextureFromImage(std::string filepath)
{
	DestroyTexture();

	SDL_Surface *loadedsurface = IMG_Load( filepath.c_str() );

	if (loadedsurface == NULL) 
	{
		return -1;
	}

	imageheight = loadedsurface->h;
	imagewidth = loadedsurface->w;

	texture = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), loadedsurface);
	SDL_FreeSurface(loadedsurface);

	return 0;
}

SDL_Texture *Image::GetTexture()
{
	return texture;
}

int Image::GetWidth()
{
	return imagewidth;
}

int Image::GetHeight()
{
	return imageheight;
}

void Image::DestroyTexture()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		imagewidth= 0;
		imageheight = 0;
	}
}
