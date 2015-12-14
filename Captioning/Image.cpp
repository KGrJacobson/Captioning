#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Image.h"
#include "SDLUtility.h"

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

	imageheight_ = loadedsurface->h;
	imagewidth_ = loadedsurface->w;

	texture_ = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), loadedsurface);
	SDL_FreeSurface(loadedsurface);

	return 0;
}

SDL_Texture *Image::GetTexture()
{
	return texture_;
}

int Image::GetWidth()
{
	return imagewidth_;
}

int Image::GetHeight()
{
	return imageheight_;
}

void Image::DestroyTexture()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		imagewidth_ = 0;
		imageheight_ = 0;
	}
}
