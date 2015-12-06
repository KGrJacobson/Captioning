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

	int mouseevent = NO_MOUSE_STATE;
	bool ismousedown = false;
	bool foundactive = false;
	
	MouseHandler x;
	x.Init(100, 100, 100, 100);
	activemice.push_back(&x);

	while (!quit) {
		SDLUtility::ClearScreen();
		previousmousevent = currentmouseevent;

		if (ismousedown != true)
			mouseevent = MOUSEOVER;

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				ismousedown = true;
				mouseevent = e.button.button;
			}

			if (e.type == SDL_MOUSEBUTTONUP)
			{
				ismousedown = false;
				mouseevent = e.button.button;
			}

			//if (e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT))
			//	shift = false;

			//if (e.type == SDL_KEYDOWN)
			//{
			//	if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT)
			//		shift = true;

			//	if (e.key.keysym.sym == SDLK_RETURN) {}
			//		//x.CreateString(&c);

			//	x.KeyboardInput(&e, shift);
			//}
		}

		foundactive = false;
		for (std::list<MouseHandler*>::iterator it = activemice.begin(); it != activemice.end(); it++)
		{
			if ((*it)->IsActive() == true)
			{
				currentmouseevent = (*it);
				foundactive = true;
			}
		}

		if (foundactive == false)
			currentmouseevent = NULL;

		if (previousmousevent != NULL && previousmousevent != currentmouseevent)
			previousmousevent->ResetMouseEvents();
		
		if (currentmouseevent != NULL)
		{
			currentmouseevent->SetActive(mouseevent, ismousedown);

			switch (currentmouseevent->GetCurrentState())
			{
			case NO_MOUSE_STATE:
				currentmouseevent->ShowMouseArea(SDL_Color{ 0, 0, 0, 255 });
				break;
			case MOUSEOVER:
				currentmouseevent->ShowMouseArea(SDL_Color{ 255, 0, 0, 255 });
				break;
			case LEFT_BUTTON_DOWN:
				currentmouseevent->ShowMouseArea(SDL_Color{ 0, 255, 0, 255 });
				break;
			case RIGHT_BUTTON_DOWN:
				currentmouseevent->ShowMouseArea(SDL_Color{ 0, 0, 255, 255 });
				break;
			case LEFT_BUTTON_UP:
				DebugText::CreateMessage("left click");
				break;
			case RIGHT_BUTTON_UP:
				DebugText::CreateMessage("right click");
				break;
			default:
				currentmouseevent->ShowMouseArea(SDL_Color{ 255, 255, 255, 255 });
				break;
			}
		}
		else
		{
			x.ShowMouseArea(SDL_Color{ 0, 0, 0, 255 });
		}

		y.Show();
		//x.PostCurrentEntry(200, 50);


		DebugText::PostMessages(); 
		SDLUtility::UpdateScreen();
	}

	return 0;
}