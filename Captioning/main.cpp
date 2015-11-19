#include <iostream>
#include "SDLUtility.h"
#include "Image.h"
#include <string>
#include <SDL_image.h>
#include "SDL.h"
#include "TextInput.h"
#include "DebugText.h"
#include "ManualEntry.h"

int main(int argc, char *argv[]) {
	if (SDLUtility::Init() < 0)
	{
		std::cout << "SDL Initialization failure" << '\n';
		return 1;
	}

	ManualEntry x;
	x.InsertCharacter('a', true);

	bool quit = false;
	bool shift = false;
	SDL_Event e;

	while (!quit) {
		SDLUtility::ClearScreen();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT))
				shift = false;

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT)
					shift = true;

				x.KeyboardInput(&e, shift);
			}
		}

		x.PostCurrentEntry(50, 50);
		SDLUtility::UpdateScreen();
	}

	return 0;
}