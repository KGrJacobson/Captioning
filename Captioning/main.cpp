#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "DebugText.h"
#include "InputScreen.h"
#include "ScreenHandler.h"
#include "SDLUtility.h"

int main(int argc, char *argv[]) {
	if (SDLUtility::Init() < 0)
	{
		std::cout << "SDL Initialization failure" << '\n';
		return 1;
	}

	ScreenHandler screenhandler;

	bool quit = false;
	SDL_Event e;

	while (!quit) {
		SDLUtility::ClearScreen();

		screenhandler.PreEventMouseSetup();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else
			{
				screenhandler.HandleEvents(e);
			}
		}

		screenhandler.PostEventMouseSetup();
		screenhandler.ShowScreens();

		DebugText::PostMessages();
		SDLUtility::UpdateScreen();
	}

	return 0;
}