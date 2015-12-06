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
}

DemoScreen::~DemoScreen()
{
	captionlist.erase(captionlist.begin(), captionlist.end());
}

void DemoScreen::BuildMouseList()
{
}

bool DemoScreen::CheckMouseHandlers(int mouseaction, bool isdown)
{
	return false;
}

void DemoScreen::Show()
{
	SDL_Color demoscreencolor{ 0, 0, 0, 255 };

	SDLUtility::CreateSquare(&screenarea, &demoscreencolor);

	for (std::list<CaptionContainer*>::iterator it = captionlist.begin(); it != captionlist.end(); it++)
	{
		(*it)->ShowContainer(screenarea);
		(*it)->ShowCaption(screenarea);
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
	newcontainer->Init(text, x, y, w, screenarea.w, static_cast<int>(basefontsize * (static_cast<float>(screenarea.w) / 1600)), containerid);

	captionlist.push_back(newcontainer);
}
