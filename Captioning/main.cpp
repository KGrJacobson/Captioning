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
#include "DemoScreen.h"
#include "MouseHandler.h"
#include <list>

int main(int argc, char *argv[]) {
	if (SDLUtility::Init() < 0)
	{
		std::cout << "SDL Initialization failure" << '\n';
		return 1;
	}

	//ManualEntry x;
	DemoScreen y(22);
	y.CreateCaption("The banded sugar ant (Camponotus consobrinus) is a species of ant endemic to Australia. A member of the genus Camponotus in the subfamily Formicinae, it was described by German entomologist Wilhelm Ferdinand Erichson in 1842. Its common name refers to the ant's preference for sweet food, as well as the distinctive orange-brown band around its gaster. ", 
		.15, .80, .70, 0);

	DebugText::CreateMessage("test");
	//DebugText::CreateMessage("ŽÀŒ±");

	bool quit = false;
	bool shift = false;
	SDL_Event e;

	std::list<MouseHandler*> activemice;
	MouseHandler *previousmousevent = NULL;
	MouseHandler *currentmouseevent = NULL;

	int mouseevent;
	bool ismousedown = false;
	MouseHandler x;
	x.Init(100, 100, 100, 100);
	activemice.push_back(&x);

	while (!quit) {
		SDLUtility::ClearScreen();
		mouseevent = -1;

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.type == SDL_MOUSEBUTTONDOWN)
				

			if (e.type == e.type == SDL_MOUSEBUTTONUP)
				ismousedown = false;

			//if (e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT))
			//	shift = false;

			//if (e.type == SDL_KEYDOWN)
			//{
			//	if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT)
			//		shift = true;

			//	if (e.key.keysym.sym == SDLK_DELETE)
			//		DebugText::ClearMessages();

			//	if (e.key.keysym.sym == SDLK_RETURN) {}
			//		//x.CreateString(&c);

			//	x.KeyboardInput(&e, shift);
			//}
		}

		y.ShowScreen();
		//x.PostCurrentEntry(200, 50);
		x.ShowMouseArea();
		
		DebugText::PostMessages(); 
		SDLUtility::UpdateScreen();
	}

	return 0;
}