#include <iostream>
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Texture.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font *font = NULL;

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;

	window = SDL_CreateWindow("SDL Test",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1500, 750, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	bool quit = false;
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	 
	SDL_Quit();
	return 0;
}


