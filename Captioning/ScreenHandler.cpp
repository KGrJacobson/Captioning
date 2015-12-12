#include <list>
#include <string>
#include "DebugText.h"
#include "sdl.h"
#include "SDLUtility.h"
#include "ScreenHandler.h"
#include "Subscreen.h"
#include "DemoScreen.h"
#include "InputScreen.h"

ScreenHandler::ScreenHandler()
{
	shift = false;

	mousetoevaluate = NULL;
	previousmousevent = NULL;
	currentmouseevent = NULL;
	mouseevent = NO_MOUSE_STATE;
	ismousedown = false;

	demoscreen = new DemoScreen(22);
	demoscreen->CreateCaption("In C++ there are conditional assignment situations where use of the if-else statement is impossible, since this language explicitly distinguishes between initialization and assignment. In such case it is always possible to use a function call, but this can be cumbersome and inelegant. For example, to pass conditionally different values as an argument for a constructor of a field or a base class, it is impossible to use a plain if-else statement; in this case we can use a conditional assignment expression, or a function call.",
		.15, .80, .70, 0);
	screens.push_back(demoscreen);

	int windowh = -1;
	SDLUtility::GetScreenWH(NULL, &windowh);
	inputscreen = new InputScreen(SDL_Rect{ 0, 0, demoscreen->GetScreenSize().x, windowh });
	screens.push_back(inputscreen);
}

ScreenHandler::~ScreenHandler()
{
	delete demoscreen;
	demoscreen = NULL;
	delete inputscreen;
	inputscreen = NULL;

	screens.clear();
}

void ScreenHandler::PreEventMouseSetup()
{
	previousmousevent = currentmouseevent;

	if (ismousedown != true)
		mouseevent = MOUSEOVER;
}

void ScreenHandler::HandleEvents(const SDL_Event &e)
{

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

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_DELETE:
			demoscreen->ClearAllCaptionText();
			break;
		}
	}

	if (e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT))
		shift = false;

	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT)
			shift = true;

		if (e.key.keysym.sym == SDLK_RETURN)
			demoscreen->SetCaptionText(inputscreen->PostText(), -1);

		inputscreen->KeyboardInput(e, shift);
	}
}

void ScreenHandler::PostEventMouseSetup()
{
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
}

void ScreenHandler::ShowScreens()
{
	for (std::list<Subscreen*>::iterator it = screens.begin(); it != screens.end(); it++)
	{
		(*it)->Show();
	}
}

int ScreenHandler::GetCurrentMouseState(int mouseevent, bool isdown)
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