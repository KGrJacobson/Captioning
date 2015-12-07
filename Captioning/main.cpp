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
#include "Subscreen.h"

int GetCurrentMouseState(int mouseevent, bool isdown)
{
	if (mouseevent == MOUSEOVER)
		return MOUSEOVER;

	if (isdown == true)
	{
		if (mouseevent == SDL_BUTTON_LEFT)
		{
			return LEFT_BUTTON_DOWN;
		}
		else
		{
			if (mouseevent == SDL_BUTTON_RIGHT)
				return RIGHT_BUTTON_DOWN;
		}
	}
	else
	{
		if (mouseevent == SDL_BUTTON_LEFT)
		{
			return LEFT_BUTTON_UP;
		}
		else
		{
			if (mouseevent == SDL_BUTTON_RIGHT)
				return RIGHT_BUTTON_UP;
		}
	}

	return NO_MOUSE_STATE;
}

int main(int argc, char *argv[]) {
	if (SDLUtility::Init() < 0)
	{
		std::cout << "SDL Initialization failure" << '\n';
		return 1;
	}

	//ManualEntry x;
	std::list<Subscreen*> screens;
	
	DemoScreen demoscreen(22);
	demoscreen.CreateCaption("In C++ there are conditional assignment situations where use of the if-else statement is impossible, since this language explicitly distinguishes between initialization and assignment. In such case it is always possible to use a function call, but this can be cumbersome and inelegant. For example, to pass conditionally different values as an argument for a constructor of a field or a base class, it is impossible to use a plain if-else statement; in this case we can use a conditional assignment expression, or a function call.", 
		.15, .80, .70, 0);
	screens.push_back(&demoscreen);

	DebugText::CreateMessage("test");
	//DebugText::CreateMessage("ŽÀŒ±");

	bool quit = false;
	bool shift = false;
	SDL_Event e;

	MouseHandler *mousetoevaluate = NULL;
	MouseHandler *previousmousevent = NULL;
	MouseHandler *currentmouseevent = NULL;
	int mouseevent = NO_MOUSE_STATE;
	bool ismousedown = false;

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

		currentmouseevent = NULL;
		for (std::list<Subscreen*>::iterator it = screens.begin(); it != screens.end(); it++)
		{
			mousetoevaluate = (*it)->CheckMouseHandlers(GetCurrentMouseState(mouseevent, ismousedown));

			if (mousetoevaluate != NULL)
			{
				currentmouseevent = mousetoevaluate;
			}
		}

		if (previousmousevent != NULL && previousmousevent != currentmouseevent)
			previousmousevent->ResetMouseEvents();
		
		if (currentmouseevent != NULL)
		{
			currentmouseevent->SetEvent(GetCurrentMouseState(mouseevent, ismousedown));
		}

		for (std::list<Subscreen*>::iterator it = screens.begin(); it != screens.end(); it++)
		{
			(*it)->Show();
		}

		//x.PostCurrentEntry(200, 50);

		DebugText::PostMessages();
		SDLUtility::UpdateScreen();
	}

	return 0;
}


//switch (mousefunction.GetEvent())
//{
//case MOUSEOVER:
//	mousefunction.ShowMouseArea(SDL_Color{ 255, 0, 0, 55 });
//	break;
//case LEFT_BUTTON_DOWN:
//	mousefunction.ShowMouseArea(SDL_Color{ 0, 255, 0, 55 });
//	break;
//case RIGHT_BUTTON_DOWN:
//	mousefunction.ShowMouseArea(SDL_Color{ 0, 0, 255, 55 });
//	break;
//case LEFT_BUTTON_UP:
//	DebugText::CreateMessage("leftclick");
//	break;
//case RIGHT_BUTTON_UP:
//	DebugText::CreateMessage("rightclick");
//	break;
//}