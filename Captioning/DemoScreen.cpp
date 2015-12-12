#include "DemoScreen.h"
#include <list>
#include <string>
#include "SDL.h"
#include "SDLUtility.h"
#include "CaptionContainer.h"
#include "DebugText.h"
#include "MouseHandler.h"
#include <algorithm>
#include <stdlib.h>

DemoScreen::DemoScreen(int setfontize)
{
	basefontsize = setfontize;

	int w;
	SDLUtility::GetScreenWH(&w, NULL);
	selectedcaption = NULL;
	drawncaptionarea = NULL;

	screenarea = SDL_Rect{
				w - (aspectratiox * magnification),
				0,
				w - (w - (aspectratiox * magnification)),
				aspectratioy * magnification };

	mousefunction.Init(screenarea.x, screenarea.y, screenarea.w, screenarea.h);
}

DemoScreen::~DemoScreen()
{
	DeleteAllCaptions();
	delete drawncaptionarea;
	drawncaptionarea = NULL;
}

void DemoScreen::DrawNewCaption()
{
	if (drawncaptionarea == NULL)
	{
		drawncaptionarea = new SDL_Rect;
		SDL_GetMouseState(&drawncaptionarea->x, &drawncaptionarea->y);
		drawncaptionarea->w = 0;
		drawncaptionarea->h = 0;
	}
	else
	{
		int mousex, mousey;
		SDL_GetMouseState(&mousex, &mousey);

		drawncaptionarea->w = mousex - drawncaptionarea->x;
		drawncaptionarea->h = mousey - drawncaptionarea->y;
	}
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

SDL_Rect DemoScreen::GetScreenSize()
{
	return screenarea;
}

void DemoScreen::Show()
{
	SDL_Color demoscreencolor{ 0, 0, 0, 255 };
	SDL_Color drawnrectcolor{ 255, 0, 255, 50 };

	SDLUtility::CreateSquare(&screenarea, &demoscreencolor);

	switch (mousefunction.GetEvent())
	{
	case NO_MOUSE_STATE:
		if (drawncaptionarea != NULL)
		{
			delete drawncaptionarea;
			drawncaptionarea = NULL;
		}
		break;
	case LEFT_BUTTON_DOWN:
		DrawNewCaption();
		SDLUtility::CreateSquare(drawncaptionarea, &drawnrectcolor);
		break;
	case LEFT_BUTTON_UP:
		if (drawncaptionarea != NULL)
		{
			int drawnx = std::min(drawncaptionarea->x, drawncaptionarea->x + drawncaptionarea->w);
			int drawny = std::min(drawncaptionarea->y, drawncaptionarea->y + drawncaptionarea->h);
			int drawnw = abs(drawncaptionarea->w);
			if (drawnw > 40)
			{
				CreateCaption("",
					static_cast<double>(drawnx - screenarea.x) / static_cast<double>(screenarea.w),
					static_cast<double>(drawny - screenarea.y) / static_cast<double>(screenarea.h),
					static_cast<double>(drawnw) / static_cast<double>(screenarea.w),
					-1);
				
				if (selectedcaption != NULL)
				{
					selectedcaption->DeselectCaption();
				}
				captionlist.back()->SelectCaption();
				selectedcaption = captionlist.back();
			}

			delete drawncaptionarea;
			drawncaptionarea = NULL;
		}
		break;
	}

	int captioncode = DEFAULT;
	std::list<CaptionContainer*>::iterator it = captionlist.begin(); 
	while (it != captionlist.end())
	{
		captioncode = (*it)->EvaluateCaption(true);

		switch (captioncode)
		{
		case SELECT_CAPTION:
			if ((*it) == selectedcaption)
			{
				selectedcaption->DeselectCaption();
				selectedcaption = NULL;
			}
			else
			{
				if (selectedcaption != NULL)
				{
					selectedcaption->DeselectCaption();
				}

				selectedcaption = (*it);
			}
			break;
		}

		if (captioncode == DELETE_CAPTION)
		{
			if ((*it) == selectedcaption)
			{
				selectedcaption = NULL;
			}

			captionlist.erase(it++);
		}
		else
			++it;
	}
}

bool DemoScreen::SetCaptionText(std::string text, int captionid)
{
	if (selectedcaption != NULL)
	{
		selectedcaption->SetText(text, screenarea.w);
		return true;
	}
	else
	{
		for (std::list<CaptionContainer*>::iterator it = captionlist.begin(); it != captionlist.end(); it++)
		{
			if ((*it)->GetID() == captionid)
			{
				(*it)->SetText(text, screenarea.w);

				return true;
			}
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

void DemoScreen::ClearAllCaptionText()
{
	for (std::list<CaptionContainer*>::iterator it = captionlist.begin(); it != captionlist.end(); it++)
	{
		(*it)->SetText("", screenarea.w);
	}
}

void DemoScreen::DeleteAllCaptions()
{
	captionlist.clear();
}
