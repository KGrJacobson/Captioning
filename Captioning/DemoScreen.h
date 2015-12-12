#pragma once
#include <list>
#include <string>
#include "SDL.h"
#include "SDLUtility.h"
#include "CaptionContainer.h"
#include "DebugText.h"
#include "Subscreen.h"
#include "MouseHandler.h"

static const int aspectratiox = 16;
static const int aspectratioy = 9;
static int magnification = 40;

class DemoScreen : public Subscreen
{
public:
	DemoScreen(int setfontsizeint);
	~DemoScreen();
	void DrawNewCaption();
	MouseHandler *CheckMouseHandlers(int mouseevent);
	SDL_Rect GetScreenSize();
	void Show();
	bool SetCaptionText(std::string text, int captionid);
	void CreateCaption(std::string text, double x, double y, double w, int containerid);
	void ClearAllCaptionText();
	void DeleteAllCaptions();
private: 
	int basefontsize;
	MouseHandler mousefunction;
	SDL_Rect screenarea;
	SDL_Rect *drawncaptionarea;
	CaptionContainer *selectedcaption;
	std::list<CaptionContainer*> captionlist;
};