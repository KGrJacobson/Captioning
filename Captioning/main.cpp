#include <iostream>
#include "SDLUtility.h"
#include "Image.h"
#include <string>
#include <SDL_image.h>
#include "SDL.h"
#include "TextInput.h"
#include "DebugText.h"
#include "ManualEntry.h"
#include "CaptionContainer.h"

int main(int argc, char *argv[]) {
	if (SDLUtility::Init() < 0)
	{
		std::cout << "SDL Initialization failure" << '\n';
		return 1;
	}

	ManualEntry x;
	CaptionContainer c; 
	c.Init("But I must explain to you how all this mistaken idea of denouncing of a pleasure and praising pain was born and I will give you a complete account of the system, and expound the actual teachings of the great explorer of the truth, the master-builder of human happiness. No one rejects, dislikes, or avoids pleasure itself, because it is pleasure, but because those who do not know how to pursue pleasure rationally encounter consequences that are extremely painful. Nor again is there anyone who loves or pursues or desires to obtain pain of itself, because it is pain, but occasionally circumstances occur in which toil and pain can procure him some great pleasure. To take a trivial example, which of us ever undertakes laborious physical exercise, except to obtain some advantage from it? But who has any right to find fault with a man who chooses to enjoy a pleasure that has no annoying consequences, or one who avoids a pain that produces no resultant pleasure?",
		200, 100, 600);

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

				if (e.key.keysym.sym == SDLK_DELETE)
					DebugText::ClearMessages();

				if (e.key.keysym.sym == SDLK_RETURN)
					x.CreateString(&c);

				x.KeyboardInput(&e, shift);
			}
		}

		x.PostCurrentEntry(200, 50);
		c.ShowContainer();
		c.ShowCaption();
		
		DebugText::PostMessages(); 
		SDLUtility::UpdateScreen();
	}

	return 0;
}