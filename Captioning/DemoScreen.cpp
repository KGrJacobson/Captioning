#include <algorithm>
#include <list>
#include <stdlib.h>
#include <string>

#include "SDL.h"

#include "CaptionContainer.h"
#include "DebugText.h"
#include "DemoScreen.h"
#include "DemoScreenTab.h"
#include "MouseHandler.h"
#include "SDLUtility.h"
#include "UIElements.h"

DemoScreen::DemoScreen(int setfontize)
{
	basefontsize_ = setfontize;

	int w = SDLUtility::GetScreenWidth();
	selectedcaption_ = NULL;
	drawncaptionarea_ = NULL;

	screenarea_ = SDL_Rect{
		w - (ASPECT_RATIO_X * MAGNIFICATION_MULTIPLIER),
		0,
		w - (w - (ASPECT_RATIO_X * MAGNIFICATION_MULTIPLIER)),
		(ASPECT_RATIO_Y * MAGNIFICATION_MULTIPLIER) + DEMOSCREEN_TAB_HEIGHT };

	demoarea_ = SDL_Rect{
				w - (ASPECT_RATIO_X * MAGNIFICATION_MULTIPLIER),
				0 + DEMOSCREEN_TAB_HEIGHT,
				w - (w - (ASPECT_RATIO_X * MAGNIFICATION_MULTIPLIER)),
				ASPECT_RATIO_Y * MAGNIFICATION_MULTIPLIER };

	mousefunction_.Init(demoarea_);
}

DemoScreen::~DemoScreen()
{
	DeleteAllCaptions();
	delete drawncaptionarea_;
	drawncaptionarea_ = NULL;
}

void DemoScreen::DrawNewCaption()
{
	if (drawncaptionarea_ == NULL)
	{
		drawncaptionarea_ = new SDL_Rect;
		SDL_GetMouseState(&drawncaptionarea_->x, &drawncaptionarea_->y);
		drawncaptionarea_->w = 0;
		drawncaptionarea_->h = 0;
	}
	else
	{
		int mousex, mousey;
		SDL_GetMouseState(&mousex, &mousey);

		drawncaptionarea_->w = mousex - drawncaptionarea_->x;
		drawncaptionarea_->h = mousey - drawncaptionarea_->y;
	}
}


MouseHandler *DemoScreen::CheckMouseHandlers(int mouseevent)
{
	MouseHandler *foundmouse = NULL;

	if (SDLUtility::IsMouseActive(screenarea_))
	{
		if (SDLUtility::IsMouseActive(mousefunction_.GetMouseArea()))
		{
			foundmouse = &mousefunction_;
		}

		MouseHandler *currentevaluation = NULL;
		for (std::list<CaptionContainer*>::iterator it = captionlist_.begin(); it != captionlist_.end(); ++it)
		{
			currentevaluation = (*it)->CheckMouseEvents(mouseevent);

			if (currentevaluation != NULL)
				foundmouse = currentevaluation;
		}
	}

	return foundmouse;
}

SDL_Rect DemoScreen::GetScreenSize()
{
	return screenarea_;
}

int DemoScreen::Show()
{
	SDLUtility::CreateSquare(demoarea_, UIElements::GetUIElementColor(UIElements::DEMO_SCREEN_COLOR, UIElements::SOLID_COLOR));

	switch (mousefunction_.GetEvent())
	{
	case NO_MOUSE_STATE:
		if (drawncaptionarea_ != NULL)
		{
			delete drawncaptionarea_;
			drawncaptionarea_ = NULL;
		}
		break;
	case LEFT_BUTTON_DOWN:
		DrawNewCaption();
		SDLUtility::CreateSquare(
			(*drawncaptionarea_), 
			UIElements::GetUIElementColor(UIElements::CAPTION_CONTAINER_DRAWN_CAPTION_COLOR,
			UIElements::SEMITRANSPARENT_COLOR));
		break;
	case LEFT_BUTTON_UP:
		if (drawncaptionarea_ != NULL)
		{
			int drawnx = std::min(drawncaptionarea_->x, drawncaptionarea_->x + drawncaptionarea_->w);
			int drawny = std::min(drawncaptionarea_->y, drawncaptionarea_->y + drawncaptionarea_->h);
			int drawnw = abs(drawncaptionarea_->w);
			if (drawnw > 40)
			{
				CreateCaption("",
					static_cast<double>(drawnx - demoarea_.x) / static_cast<double>(demoarea_.w),
					static_cast<double>(drawny - demoarea_.y) / static_cast<double>(demoarea_.h),
					static_cast<double>(drawnw) / static_cast<double>(demoarea_.w),
					-1);
				
				if (selectedcaption_ != NULL)
				{
					selectedcaption_->DeselectCaption();
				}
				captionlist_.back()->SelectCaption();
				selectedcaption_ = captionlist_.back();
			}

			delete drawncaptionarea_;
			drawncaptionarea_ = NULL;
		}
		break;
	}

	int captioncode = DEFAULT;
	int mousex = -1;
	int mousey = -1;
	std::list<CaptionContainer*>::iterator it = captionlist_.begin(); 
	while (it != captionlist_.end())
	{
		captioncode = (*it)->EvaluateCaption(true);

		switch (captioncode)
		{
		case SELECT_CAPTION:
			if ((*it) == selectedcaption_)
			{
				selectedcaption_->DeselectCaption();
				selectedcaption_ = NULL;
			}
			else
			{
				if (selectedcaption_ != NULL)
				{
					selectedcaption_->DeselectCaption();
				}

				selectedcaption_ = (*it);
			}
			break;
		case MOVE_CAPTION:
			SDL_GetMouseState(&mousex, &mousey);
			(*it)->SetXY(mousex, mousey);
			break;
		}

		if (captioncode == DELETE_CAPTION)
		{
			if ((*it) == selectedcaption_)
			{
				selectedcaption_ = NULL;
			}

			captionlist_.erase(it++);
		}
		else
			++it;
	}

	return 0;
}

bool DemoScreen::SetCaptionText(std::string text, int captionid)
{
	if (selectedcaption_ != NULL)
	{
		selectedcaption_->SetText(text, demoarea_.w);
		return true;
	}
	else
	{
		for (std::list<CaptionContainer*>::iterator it = captionlist_.begin(); it != captionlist_.end(); it++)
		{
			if ((*it)->GetID() == captionid)
			{
				(*it)->SetText(text, demoarea_.w);

				return true;
			}
		}
	}

	return false;
}

std::string DemoScreen::GetSelectedCaptionText()
{
	if (selectedcaption_ != NULL)
	{
		return selectedcaption_->GetText();
	}
	
	return "";
}

void DemoScreen::CreateCaption(std::string text, double x, double y, double w, int containerid)
{
	CaptionContainer *newcontainer = new CaptionContainer;
	newcontainer->Init(text, x, y, w, demoarea_, static_cast<int>(basefontsize_ * (static_cast<double>(demoarea_.w) / (ASPECT_RATIO_X * 100))), containerid);

	captionlist_.push_back(newcontainer);
}

void DemoScreen::ClearAllCaptionText()
{
	for (std::list<CaptionContainer*>::iterator it = captionlist_.begin(); it != captionlist_.end(); it++)
	{
		(*it)->SetText("", demoarea_.w);
	}
}

void DemoScreen::DeleteAllCaptions()
{
	captionlist_.clear();
}
