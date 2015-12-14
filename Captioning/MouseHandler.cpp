#include "MouseHandler.h"
#include "SDLUtility.h"
#include "SDL.h"
#include "DebugText.h"

void MouseHandler::Init(int x, int y, int w, int h)
{
	SetMouseArea(x, y, w, h);
	ticks_ = 0;
	mouseevent_ = NO_MOUSE_STATE;
}

void MouseHandler::SetEvent(int eventtype)
{
	mouseevent_ = eventtype;
}

int MouseHandler::GetEvent()
{
	return mouseevent_;
}

void MouseHandler::SetMouseArea(int x, int y, int w, int h)
{
	mousearea_.x = x;
	mousearea_.y = y;
	mousearea_.w = w;
	mousearea_.h = h;
}

SDL_Rect *MouseHandler::GetMouseArea()
{
	return &mousearea_;
}

void MouseHandler::ShowMouseArea(SDL_Color setcolor)
{
	SDL_Color color = setcolor;

	SDLUtility::CreateSquare(&mousearea_, &color);
}

void MouseHandler::ResetMouseEvents()
{
	mouseevent_ = NO_MOUSE_STATE;
	ticks_ = 0;
}
