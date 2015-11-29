#pragma once
#include <list>
#include <string>
#include "SDL.h"
#include "SDLUtility.h"
#include "CaptionContainer.h"
#include "DebugText.h"

static int aspectratiox = 16;
static int aspectratioy = 9;
static int magnification = 40;

class DemoScreen 
{
public:
	DemoScreen(int setfontsizeint);
	~DemoScreen();
	void ShowScreen();
	bool SetCaptionText(std::string text, int captionid);
	void CreateCaption(std::string text, float x, float y, float w, int containerid);
private: 
	int basefontsize;
	SDL_Rect demoarea;
	std::list<CaptionContainer*> captionlist;
};