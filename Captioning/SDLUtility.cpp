#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "DebugText.h"
#include "SDLUtility.h"

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

	CreateColorArray();

	return 0;
}

void SDLUtility::CreateColorArray()
{
	standardcolorvector = std::vector<SDL_Color>{
		SDL_Color{ 23, 20, 18, 255 },
		SDL_Color{ 235, 246, 247, 255 },
		SDL_Color{ 135, 95, 154, 255 },
		SDL_Color{ 151, 110, 154, 255 },
		SDL_Color{ 43, 32, 40, 255 },
		SDL_Color{ 168, 124, 160, 255 },
		SDL_Color{ 91, 50, 86, 255 },
		SDL_Color{ 35, 25, 30, 255 },
		SDL_Color{ 187, 119, 150, 255 },
		SDL_Color{ 117, 93, 91, 255 },
		SDL_Color{ 109, 43, 80, 255 },
		SDL_Color{ 164, 52, 93, 255 },
		SDL_Color{ 67, 36, 42, 255 },
		SDL_Color{ 126, 38, 57, 255 },
		SDL_Color{ 68, 49, 46, 255 },
		SDL_Color{ 93, 63, 106, 255 },
		SDL_Color{ 63, 49, 58, 255 },
		SDL_Color{ 58, 36, 59, 255 },
		SDL_Color{ 141, 96, 140, 255 },
		SDL_Color{ 79, 40, 75, 255 },
		SDL_Color{ 118, 53, 104, 255 },
		SDL_Color{ 73, 30, 60, 255 },
		SDL_Color{ 99, 66, 75, 255 },
		SDL_Color{ 77, 59, 60, 255 },
		SDL_Color{ 143, 65, 85, 255 },
		SDL_Color{ 81, 44, 49, 255 },
		SDL_Color{ 89, 41, 44, 255 }
	};
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

int SDLUtility::GetScreenWidth()
{
	return SCREENW;
}

int SDLUtility::GetScreenHeight()
{
	return SCREENH;
}

SDL_Color SDLUtility::GetSDLColor(int color, int alphavalue)
{
	SDL_Color colortoreturn = standardcolorvector[color];
	colortoreturn.a = alphavalue;

	return colortoreturn;
}

void SDLUtility::ClearScreen()
{
	SDL_RenderClear(renderer);
}

void SDLUtility::UpdateScreen()
{
	SDL_Color drawcolor = GetSDLColor(VIOLET, SOLID_COLOR);

	SDL_SetRenderDrawColor(renderer, drawcolor.r, drawcolor.g, drawcolor.b, drawcolor.a);

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

void SDLUtility::PostImage(SDL_Texture *texure, int x, int y)
{
	SDL_RenderCopy(renderer, texure, NULL, NULL);
}

void SDLUtility::PostImage(Image *img, int x, int y, SDL_Rect sourcerect)
{
	SDL_Rect destrect{ x, y, sourcerect.w, sourcerect.h };

	SDL_RenderCopy(renderer, img->GetTexture(), &sourcerect, &destrect);
}

void SDLUtility::CreateSquare(SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RenderFillRect(renderer, &rect);
}

bool SDLUtility::IsMouseActive(SDL_Rect mousecheckarea)
{
	int mousex = -1;
	int mousey = -1;
	SDL_GetMouseState(&mousex, &mousey);

	if (mousex >= mousecheckarea.x && mousey >= mousecheckarea.y &&
		mousex <= mousecheckarea.x + mousecheckarea.w && mousey <= mousecheckarea.y + mousecheckarea.h)
	{
		return true;
	}

	return false;
}
