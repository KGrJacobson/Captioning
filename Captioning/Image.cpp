#include "Image.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "SDLUtility.h"

Image::~Image()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}

int Image::CreateTextureFromImage(std::string filepath)
{
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

void Image::CreateTextureFromText(std::string text)
{
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

