#include "SDLUtility.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>

int SDLUtility::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;

	window = SDL_CreateWindow("SDL Test",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1500, 750, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	int pngflag = IMG_INIT_PNG;
	if (!(IMG_Init(pngflag)))
		return -3;

	if (window == NULL || renderer == NULL)
		return -2;

	return 0;
}

void SDLUtility::Close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	SDL_Quit();
}

SDL_Renderer *SDLUtility::GetRenderer()
{
	return renderer;
}

void SDLUtility::ClearScreen()
{
	SDL_RenderClear(renderer);
}

void SDLUtility::UpdateScreen()
{
	SDL_RenderPresent(renderer);
}

void SDLUtility::PostImage(Image *img, int x, int y)
{
	SDL_Rect sourcerect{ x, y, img->GetWidth(), img->GetHeight() };

	SDL_RenderCopy(renderer, img->GetTexture(), NULL, &sourcerect);
}

void SDLUtility::PostImage(SDL_Texture *tex, int x, int y)
{
	SDL_RenderCopy(renderer, tex, NULL, NULL);
}

