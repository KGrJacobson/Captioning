#include "SDLUtility.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include "DebugText.h"

int SDLUtility::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;

	window = SDL_CreateWindow("SDL Test",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREENW, SCREENH, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	int pngflag = IMG_INIT_PNG;
	if (!(IMG_Init(pngflag)))
	{
		std::cout << "could not initialize IMG PNG" << '\n';
		return -1;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "could not initialize TTF" << '\n';
		return -1;
	}

	if (window == NULL || renderer == NULL)
	{
		std::cout << "could not create window/renderer" << '\n';
		return -1;
	}

	return 0;
}

void SDLUtility::Close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	TTF_Quit(); 
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer *SDLUtility::GetRenderer()
{
	return renderer;
}

void SDLUtility::GetScreenWH(int *w, int *h)
{
	if (w != NULL)
		*(w) = SCREENW;
	
	if (h != NULL)
		*(h) = SCREENH;
}

void SDLUtility::ClearScreen()
{
	SDL_RenderClear(renderer);
}

void SDLUtility::UpdateScreen()
{
	SDL_SetRenderDrawColor(renderer, 102, 0, 75, 255);

	SDL_RenderPresent(renderer);
}

void SDLUtility::PostImage(Image *img, int x, int y)
{
	SDL_Rect destrect{ x, y, img->GetWidth(), img->GetHeight() };

	SDL_RenderCopy(renderer, img->GetTexture(), NULL, &destrect);
}

void SDLUtility::PostText(TextInput *text, int x, int y)
{
	SDL_Rect destrect{ x, y, text->GetWidth(), text->GetHeight() };

	SDL_RenderCopy(renderer, text->GetTexture(), NULL, &destrect);
}

void SDLUtility::PostImage(SDL_Texture *tex, int x, int y)
{
	SDL_RenderCopy(renderer, tex, NULL, NULL);
}

void SDLUtility::PostImage(Image *img, int x, int y, SDL_Rect *sourcerect)
{
	SDL_Rect destrect{ x, y, sourcerect->w, sourcerect->h };

	SDL_RenderCopy(renderer, img->GetTexture(), sourcerect, &destrect);
}

void SDLUtility::CreateSquare(SDL_Rect *rect, SDL_Color *color)
{
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

	SDL_RenderFillRect(renderer, rect);
}


bool SDLUtility::IsMouseActive(SDL_Rect *mousecheckarea)
{
	int mousex = -1;
	int mousey = -1;
	SDL_GetMouseState(&mousex, &mousey);

	if (mousex >= mousecheckarea->x && mousey >= mousecheckarea->y &&
		mousex <= mousecheckarea->x + mousecheckarea->w && mousey <= mousecheckarea->y + mousecheckarea->h)
	{
		return true;
	}

	return false;
}
