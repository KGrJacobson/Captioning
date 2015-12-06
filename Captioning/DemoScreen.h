#pragma once
#include <list>
#include <string>
#include "SDL.h"
#include "SDLUtility.h"
#include "CaptionContainer.h"
#include "DebugText.h"
#include "Subscreen.h"
#include "MouseHandler.h"

static int aspectratiox = 16;
static int aspectratioy = 9;
static int magnification = 40;

class DemoScreen : public Subscreen
{
public:
	DemoScreen(int setfontsizeint);
	~DemoScreen();
	void BuildMouseList();
	bool CheckMouseHandlers(int mouseaction, bool isdown);
	void Show();
	bool SetCaptionText(std::string text, int captionid);
	void CreateCaption(std::string text, double x, double y, double w, int containerid);
private: 
	int basefontsize;
	std::list<MouseHandler*> mouselist;
	SDL_Rect screenarea;
	std::list<CaptionContainer*> captionlist;
};