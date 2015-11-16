#include <iostream>
#include "SDLUtility.h"
#include "Image.h"
#include <string>
#include <SDL_image.h>
#include "SDL.h"
#include "TextInput.h"

int main(int argc, char *argv[]) {
	if (SDLUtility::Init() < 0)
	{
		std::cout << "SDL Initialization failure" << '\n';
		return 1;
	}

	TextInput test(75);
	test.CreateTextureFromText("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

	bool quit = false;
	SDL_Event e;

	while (!quit) {
		SDLUtility::ClearScreen();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDLUtility::PostText(&test, 100, 100);
		SDLUtility::UpdateScreen();
	}

	return 0;
}