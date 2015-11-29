#include "DemoScreen.h"
#include <list>
#include <string>
#include "SDL.h"
#include "SDLUtility.h"
#include "CaptionContainer.h"
#include "DebugText.h"

DemoScreen::DemoScreen(int setfontize)
{
	basefontsize = setfontize;

	int w;
	SDLUtility::GetScreenWH(&w, NULL);

	demoarea = SDL_Rect{
				w - (aspectratiox * magnification),
				0,
				w - (w - (aspectratiox * magnification)),
				aspectratioy * magnification };
}

DemoScreen::~DemoScreen()
{
	captionlist.erase(captionlist.begin(), captionlist.end());
}

void DemoScreen::ShowScreen()
{
	SDL_Color demoscreencolor{ 0, 0, 0, 255 };

	SDLUtility::CreateSquare(&demoarea, &demoscreencolor);

	for (std::list<CaptionContainer*>::iterator it = captionlist.begin(); it != captionlist.end(); it++)
	{
		(*it)->ShowContainer(demoarea);
		(*it)->ShowCaption(demoarea);
	}
}

bool DemoScreen::SetCaptionText(std::string text, int captionid)
{
	for (std::list<CaptionContainer*>::iterator it = captionlist.begin(); it != captionlist.end(); it++)
	{
		if ((*it)->GetID() == captionid) 
		{
			(*it)->SetText(text, demoarea.w);

			return true;
		}
	}

	return false;
}

void DemoScreen::CreateCaption(std::string text, float x, float y, float w, int containerid)
{
	CaptionContainer *newcontainer = new CaptionContainer;
	newcontainer->Init(text, x, y, w, demoarea.w, static_cast<int>(basefontsize * (static_cast<float>(demoarea.w) / 1600)), containerid);

	captionlist.push_back(newcontainer);
}
