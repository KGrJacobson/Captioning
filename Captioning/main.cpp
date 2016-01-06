#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "KWindow\DebugText.h"
#include "KWindow\InputHandler.h"
#include "ScreenHandler.h"
#include "KWindow\SDLUtility.h"

//Contains initialization functions and the basic program loop.  Returns 1 if initialization fails.
int main(int argc, char *argv[]) {
	//Initialize all functions for SDL and KWindow.
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

	//close SDL and KWindow
	InputHandler::CloseInputs();
	//SDLUtility::Close();
	return 0;
}