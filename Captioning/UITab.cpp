#include <list>

#include "SDL.h"

#include "CaptionContainer.h"
#include "UITab.h"
#include "MouseHandler.h"
#include "SDLUtility.h"
#include "UIElements.h"
#include "UIButton.h"

UITab::UITab(SDL_Rect tabarea, std::string text, int tabnumber)
{
	tabnumber_ = tabnumber;
	tabarea_ = tabarea;
	tabbutton_ = new UIButton(tabarea, text, false);
	closebutton_ = new UIButton(SDL_Rect{ tabarea.x, tabarea.y, 20, UIElements::STANDARD_TAB_HEIGHT }, "X", true);
}

UITab::~UITab()
{
	delete tabbutton_;
	tabbutton_ = NULL;
	delete closebutton_;
	closebutton_ = NULL;
}

MouseHandler *UITab::CheckMouseEvents()
{
	MouseHandler *foundmouse = NULL;

	MouseHandler *currentmousehandler = NULL;
	if (SDLUtility::IsMouseActive(tabarea_))
	{
		currentmousehandler = tabbutton_->CheckMouseHandler();

		if (currentmousehandler != NULL)
			foundmouse = currentmousehandler;

		currentmousehandler = closebutton_->CheckMouseHandler();

		if (currentmousehandler != NULL)
			foundmouse = currentmousehandler;
	}

	return foundmouse;
}

int UITab::ShowTab()
{
	//UIElements::
	UIElements::ShowUITinyButton(closebutton_);

	return 0;
}

void UITab::SetTabArea(SDL_Rect newarea)
{
	tabarea_ = newarea;
	tabbutton_->SetButtonArea(newarea);
}

void UITab::SetTabNumber(int number)
{
	tabnumber_ = number;
}

int UITab::GetTabNumber()
{
	return tabnumber_;
}

ContextMenu *UITab::GetContextMenu()
{
	return contextmenu_;
}
