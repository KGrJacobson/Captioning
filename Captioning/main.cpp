#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "DebugText.h"
#include "InputHandler.h"
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

	int macro;
	int macroreturnvalue;
	while (!quit) {
		SDLUtility::ClearScreen();

		macro = KeyboardEntry::NO_MACRO;
		macroreturnvalue = KeyboardEntry::NO_MACRO;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else
			{
				macroreturnvalue = InputHandler::HandleEvents(e);
				
				if(macroreturnvalue != KeyboardEntry::NO_MACRO)
					macro = macroreturnvalue;
			}
		}

		InputHandler::CheckMouseHandlers();
		screenhandler.ShowScreens(macro);

		DebugText::PostMessages();
		SDLUtility::UpdateScreen();
	}

	InputHandler::CloseInputs();
	//SDLUtility::Close();
	return 0;
}