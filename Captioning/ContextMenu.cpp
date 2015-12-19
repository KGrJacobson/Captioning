#include <algorithm>
#include <string>
#include <vector>

#include "SDL.h"

#include "ContextMenu.h"
#include "MouseHandler.h"
#include "SDLUtility.h"
#include "UIButton.h"
#include "UIElements.h"

ContextMenu::ContextMenu()
{
	ResetMenu();
}

ContextMenu::~ContextMenu()
{
	optionlist_.clear();
	ResetMenu();
}

int ContextMenu::GetButtonPress()
{
	return buttonpressed_;
}

void ContextMenu::ResetMenu()
{
	buttonpressed_ = -1;
	menuarea_ = SDL_Rect{ 0, 0, 0, 0 };
}

void ContextMenu::AddListItem(UIButton *newitem)
{
	optionlist_.push_back(newitem);
}

void ContextMenu::SetXY(int x, int y)
{
	int nextx = x;
	int nexty = y;
	int numberofelements = 0;

	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.end(); ++it)
	{
		if (numberofelements >= STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN)
		{
			nextx = nextx + STANDARD_CONTEXT_MENU_WIDTH;
			nexty = y;
			numberofelements = 0;
		}

		(*it)->SetButtonCoordinates(nextx, nexty);
		nexty = nexty + STANDARD_CONTEXT_MENU_HEIGHT;

		++numberofelements;
	}

	menuarea_ = SDL_Rect{
		x,
		y,
		(optionlist_.size() < STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) ? STANDARD_CONTEXT_MENU_WIDTH : 1 + static_cast<int>(static_cast<double>(optionlist_.size()) / STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN ) * STANDARD_CONTEXT_MENU_WIDTH,
		(optionlist_.size() < STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) ? nexty - y : STANDARD_CONTEXT_MENU_HEIGHT * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN
	};
}

MouseHandler *ContextMenu::CheckMouseHandlers()
{
	MouseHandler *foundmouse = NULL;

	MouseHandler *currentevaluation = NULL;
	if (SDLUtility::IsMouseActive(menuarea_))
	{
		MouseHandler *currentevaluation = NULL;
		for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.end(); ++it)
		{
			currentevaluation = (*it)->CheckMouseHandler();

			if (currentevaluation != NULL)
				foundmouse = currentevaluation;
		}
	}

	return foundmouse;
}

void ContextMenu::ShowMenu()
{
	int currentbutton = 0;
	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.end(); ++it)
	{
		UIElements::ShowUIContextMenu((*it));

		if ((*it)->GetMouseEvent() == LEFT_BUTTON_UP)
		{
			buttonpressed_ = currentbutton;
		}

		++currentbutton;
	}
}
