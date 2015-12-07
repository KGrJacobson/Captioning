#include "DemoScreen.h"
#include <list>
#include <string>
#include "SDL.h"
#include "SDLUtility.h"
#include "CaptionContainer.h"
#include "DebugText.h"
#include "MouseHandler.h"

DemoScreen::DemoScreen(int setfontize)
{
	basefontsize = setfontize;

	int w;
	SDLUtility::GetScreenWH(&w, NULL);

	screenarea = SDL_Rect{
				w - (aspectratiox * magnification),
				0,
				w - (w - (aspectratiox * magnification)),
				aspectratioy * magnification };

	mousefunction.Init(screenarea.x, screenarea.y, screenarea.w, screenarea.h);
}

DemoScreen::~DemoScreen()
{
	captionlist.clear();
}

void DemoScreen::BuildMouseList()
{
}

MouseHandler *DemoScreen::CheckMouseHandlers(int mouseevent)
{
	MouseHandler *foundmouse = NULL;

	if (SDLUtility::IsMouseActive(mousefunction.GetMouseArea()))
	{
		foundmouse = &mousefunction;
	}
	else
	{
		return NULL;
	}

	MouseHandler *currentevaluation = NULL;
	for (std::list<CaptionContainer*>::iterator it = captionlist.begin(); it != captionlist.end(); it++)
	{
		currentevaluation = (*it)->CheckMouseEvents(mouseevent);

		if (currentevaluation != NULL)
			foundmouse = currentevaluation;
	}

	return foundmouse;
}

void DemoScreen::Show()
{
	SDL_Color demoscreencolor{ 0, 0, 0, 255 };

	SDLUtility::CreateSquare(&screenarea, &demoscreencolor);

	int captioncode = DEFAULT;
	for (std::list<CaptionContainer*>::iterator it = captionlist.begin(); it != captionlist.end(); it++)
	{
		captioncode = (*it)->EvaluateCaption(true);
		//if (captioncode = DELETE_CAPTION)
		//	captionlist.erase(it++);
	}
}

bool DemoScreen::SetCaptionText(std::string text, int captionid)
{
	for (std::list<CaptionContainer*>::iterator it = captionlist.begin(); it != captionlist.end(); it++)
	{
		if ((*it)->GetID() == captionid) 
		{
			(*it)->SetText(text, screenarea.w);

			return true;
		}
	}

	return false;
}

void DemoScreen::CreateCaption(std::string text, double x, double y, double w, int containerid)
{
	CaptionContainer *newcontainer = new CaptionContainer;
	newcontainer->Init(text, x, y, w, screenarea, static_cast<int>(basefontsize * (static_cast<float>(screenarea.w) / 1600)), containerid);

	captionlist.push_back(newcontainer);
}
