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

	DebugText::CreateMessage("test");
	DebugText::CreateMessage(L"あ、アは、日本語の音節の1つであり、仮名の1つである。1モーラを形成する。五十音図において第1行第1段（あ行あ段）に位置する");

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