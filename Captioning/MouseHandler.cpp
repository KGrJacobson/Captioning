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

void MouseHandler::SetEvent(int eventtype)
{
	mouseevent = eventtype;
}

int MouseHandler::GetEvent()
{
	return mouseevent;
}

void MouseHandler::SetMouseArea(int x, int y, int w, int h)
{
	mousearea.x = x;
	mousearea.y = y;
	mousearea.w = w;
	mousearea.h = h;
}

SDL_Rect *MouseHandler::GetMouseArea()
{
	return &mousearea;
}

void MouseHandler::ShowMouseArea(SDL_Color setcolor)
{
	SDL_Color color = setcolor;

	SDLUtility::CreateSquare(&mousearea, &color);
}

void MouseHandler::ResetMouseEvents()
{
	mouseevent = NO_MOUSE_STATE;
	ticks = 0;
}
