#include <algorithm>
#include <list>
#include <stdlib.h>
#include <string>

#include "SDL.h"

#include "CaptionContainer.h"
#include "DebugText.h"
#include "DemoScreen.h"
#include "InputHandler.h"
#include "MouseHandler.h"
#include "NetworkUtility.h"
#include "SDLUtility.h"
#include "UIElements.h"
#include "UITab.h"

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
	InputHandler::AddMouseHandler(&mousefunction_);

	tablist_.push_back(new UITab(
		SDL_Rect{ screenarea_.x, screenarea_.y, UIElements::STANDARD_TAB_WIDTH, UIElements::STANDARD_TAB_HEIGHT }, 
		"Default", 
		0,
		CreateNewTabContextMenu()
		));
	captionlist_.push_back(new std::list<CaptionContainer*>);
	currenttab_ = 0;

	newtabbutton_ = new UIButton(SDL_Rect{ tablist_.back()->GetTabArea().x + tablist_.back()->GetTabArea().w , screenarea_.y, 20, 20 },
		"+",
		true);
}

DemoScreen::~DemoScreen()
{
	DeleteAllCaptions();
	delete drawncaptionarea_;
	drawncaptionarea_ = NULL;
	captionlist_.clear();
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

SDL_Rect DemoScreen::GetScreenSize()
{
	return screenarea_;
}

int DemoScreen::Show()
{
	int returncode = NO_RETURN_CODE;

	UIElements::ShowUITinyButton(newtabbutton_);
	if (newtabbutton_->GetMouseEvent() == LEFT_BUTTON_UP)
		CreateNewTab();

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
				captionlist_[currenttab_]->back()->SelectCaption();
				selectedcaption_ = captionlist_[currenttab_]->back();
			}

			delete drawncaptionarea_;
			drawncaptionarea_ = NULL;
		}
		break;
	}

	int captioncode = NO_RETURN_CODE;
	int mousex = -1;
	int mousey = -1;
	std::list<CaptionContainer*>::iterator it = captionlist_[currenttab_]->begin();
	while (it != captionlist_[currenttab_]->end())
	{
		captioncode = (*it)->Show(true);

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

			captionlist_[currenttab_]->erase(it++);
		}
		else
			++it;
	}


	int closetab = 0;
	std::vector<UITab*>::iterator tabit = tablist_.begin();
	while (tabit != tablist_.end())
	{
		bool isselected;

		if ((*tabit)->GetTabNumber() == currenttab_)
			isselected = true;
		else
			isselected = false;

		int tabcode = (*tabit)->ShowTab(isselected);

		switch (tabcode)
		{
		case UITab::CLOSE_TAB:
			closetab = (*tabit)->GetTabNumber();
			break;
		case UITab::SELECT_TAB:
			if (selectedcaption_ != NULL)
			{
				selectedcaption_->DeselectCaption();
				selectedcaption_ = NULL;
			}

			for (std::list<CaptionContainer*>::iterator removeit = captionlist_[currenttab_]->begin(); removeit != captionlist_[currenttab_]->end(); ++removeit)
			{
				(*removeit)->RemoveMouseHandler();
			}

			currenttab_ = (*tabit)->GetTabNumber();

			for (std::list<CaptionContainer*>::iterator addit = captionlist_[currenttab_]->begin(); addit != captionlist_[currenttab_]->end(); ++addit)
			{
				(*addit)->AddMouseHandler();
			}
			break;
		case UITab::MOVE_TAB:
			break;
		case UITab::OPEN_CONTEXT_MENU:
			InputHandler::SetMenu((*tabit)->GetContextMenu(), NULL, NULL);
			break;
		case UITab::CHECK_CONTEXT_MENU:
			if ((*tabit)->GetContextMenuAction() == RENAME_TAB)
			{
				InputHandler::SetKeyboardEntryTexture((*tabit)->GetTabText());
			}
			InputHandler::SetMenu(NULL, NULL, NULL);
			break;
		}

		++tabit;
	}

	if (closetab != 0)
	{
		if (tablist_.begin() + closetab == tablist_.end() - 1 && closetab == currenttab_)
		{
			currenttab_ = currenttab_ - 1;
		}

		delete tablist_.at(closetab);
		tablist_.erase(tablist_.begin() + closetab);
		captionlist_.erase(captionlist_.begin() + closetab);
	
		int newposition = 0;
		for (std::vector<UITab*>::iterator repositionit = tablist_.begin(); repositionit != tablist_.end(); ++repositionit)
		{
			(*repositionit)->SetTabNumber(newposition);
			(*repositionit)->SetTabArea(
				SDL_Rect{ screenarea_.x + (newposition * UIElements::STANDARD_TAB_WIDTH),
				screenarea_.y, 
				UIElements::STANDARD_TAB_WIDTH, 
				UIElements::STANDARD_TAB_HEIGHT }
				);
			++newposition;
		}

		newtabbutton_->SetButtonCoordinates(tablist_.back()->GetTabArea().x + tablist_.back()->GetTabArea().w, screenarea_.y);
	}

	return returncode;
}

bool DemoScreen::SetCaptionText(std::string text, int captionid)
{
	if (selectedcaption_ != NULL)
	{
		selectedcaption_->SetText(text);
		return true;
	}
	else
	{
		for (std::list<CaptionContainer*>::iterator it = captionlist_[currenttab_]->begin(); it != captionlist_[currenttab_]->end(); ++it)
		{
			if ((*it)->GetID() == captionid)
			{
				(*it)->SetText(text);

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

	captionlist_[currenttab_]->push_back(newcontainer);
}

void DemoScreen::ClearAllCaptionText()
{
	for (std::list<CaptionContainer*>::iterator it = captionlist_[currenttab_]->begin(); it != captionlist_[currenttab_]->end(); it++)
	{
		(*it)->SetText("");
	}
}

void DemoScreen::DeleteAllCaptions()
{
	captionlist_[currenttab_]->clear();
}

UIMenu *DemoScreen::CreateNewTabContextMenu()
{
	UIMenu *newcontextmenu = new UIMenu();
	newcontextmenu->AddListItem(new UIButton(SDL_Rect{ SDLUtility::GetScreenWidth(), 0, UIMenu::STANDARD_CONTEXT_MENU_WIDTH, UIMenu::STANDARD_CONTEXT_MENU_HEIGHT }, "Rename", false));

	return newcontextmenu;
}

void DemoScreen::CreateNewTab()
{
	tablist_.push_back(new UITab(
		SDL_Rect{ tablist_.back()->GetTabArea().x + tablist_.back()->GetTabArea().w , screenarea_.y, UIElements::STANDARD_TAB_WIDTH, UIElements::STANDARD_TAB_HEIGHT },
		"New Tab",
		tablist_.back()->GetTabNumber() + 1,
		CreateNewTabContextMenu()
		));
	captionlist_.push_back(new std::list<CaptionContainer*>);

	newtabbutton_->SetButtonCoordinates(tablist_.back()->GetTabArea().x + tablist_.back()->GetTabArea().w, screenarea_.y);
}
