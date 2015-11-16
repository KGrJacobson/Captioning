#include <iostream>
#include "SDLUtility.h"
#include "Image.h"
#include <string>
#include <SDL_image.h>
#include "SDL.h"

int main(int argc, char *argv[]) {
	if (SDLUtility::Init() < 0)
		return 1;

	Image gsquare;
	if (gsquare.CreateTextureFromImage("greensquare.png") == -1)
	{
		return 2;
	}


	/*int pngflag = IMG_INIT_PNG;
	if (!(IMG_Init(pngflag)))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	SDL_Surface *loadedsurface = IMG_Load("greensquare.png");

	if (loadedsurface == NULL)
	{
		std::cout << "null surface";
		return -1;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), loadedsurface);
	SDL_FreeSurface(loadedsurface);*/

	bool quit = false;
	SDL_Event e;

	while (!quit) {
		SDLUtility::ClearScreen();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDLUtility::PostImage(&gsquare, 100, 100);
		SDLUtility::UpdateScreen();
	}

	return 0;
}