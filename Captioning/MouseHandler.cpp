#include "MouseHandler.h"
#include "SDLUtility.h"
#include "SDL.h"
#include "DebugText.h"

void MouseHandler::Init(int x, int y, int w, int h)
{
	SetMouseArea(x, y, w, h);
	ticks = 0;
	mouseevent = NO_MOUSE_STATE;
}

bool MouseHandler::IsActive()
{
	int mousex = -1;
	int mousey = -1;
	SDL_GetMouseState(&mousex, &mousey);

	if (mousex >= mousearea.x && mousey >= mousearea.y &&
		mousex <= mousearea.x + mousearea.w && mousey <= mousearea.y + mousearea.h) 
	{
		return true;
	}

	return false;
}

void MouseHandler::SetActive(int eventtype, bool iscurrentdown)
{
	isactive = true;
	mouseevent = eventtype;
	isdown = iscurrentdown;
}

void MouseHandler::SetMouseArea(int x, int y, int w, int h)
{
	mousearea.x = x;
	mousearea.y = y;
	mousearea.w = w;
	mousearea.h = h;
}

void MouseHandler::ShowMouseArea(SDL_Color setcolor)
{
	SDL_Color color = setcolor;

	SDLUtility::CreateSquare(&mousearea, &color);
}

int MouseHandler::GetCurrentState()
{
	if (isactive == true)
	{
		if (mouseevent == MOUSEOVER)
			return MOUSEOVER;

		if (isdown == true)
			if (mouseevent == SDL_BUTTON_LEFT)
				return LEFT_BUTTON_DOWN;
			else
			{
				if (mouseevent == SDL_BUTTON_RIGHT)
					return RIGHT_BUTTON_DOWN;
			}
		else
			if (mouseevent == SDL_BUTTON_LEFT)
				return LEFT_BUTTON_UP;
			else
			{
				if (mouseevent == SDL_BUTTON_RIGHT)
					return RIGHT_BUTTON_UP;
			}
	}

	return NO_MOUSE_STATE;
}

void MouseHandler::ResetMouseEvents()
{
	isactive = false;
	mouseevent = NO_MOUSE_STATE;
	ticks = 0;
}
