#include "MouseHandler.h"
#include "SDLUtility.h"
#include "SDL.h"
#include "DebugText.h"

void MouseHandler::Init(int x, int y, int w, int h)
{
	SetMouseArea(x, y, w, h);
	ticks = 0;
	mouseevent = -1;
}

bool MouseHandler::IsActive()
{
	int mousex = -1;
	int mousey = -1;
	SDL_GetMouseState(&mousex, &mousey);

	if (mousex >= mousearea.x && mousey >= mousearea.y &&
		mousex <= mousearea.x + mousearea.w && mousey <= mousearea.y + mousearea.h) 
	{
		active = true;
		return true;
	}

	return false;
}

void MouseHandler::SetActive(int eventtype)
{
	mouseevent = eventtype;
}

void MouseHandler::SetMouseArea(int x, int y, int w, int h)
{
	mousearea.x = x;
	mousearea.y = y;
	mousearea.w = w;
	mousearea.h = h;
}

void MouseHandler::ShowMouseArea()
{
	SDL_Color color = SDL_Color{ 0, 0, 255, 255 };

	SDLUtility::CreateSquare(&mousearea, &color);
}

int MouseHandler::GetEvent()
{
	return mouseevent;
}

void MouseHandler::ResetMouseEvents()
{
	active = false;
	mouseevent = -1;
	ticks = 0;
}
