#include <list>
#include <string>

#include "SDL.h"

#include "ContextMenu.h"
#include "DebugText.h"
#include "DemoScreen.h"
#include "InputScreen.h"
#include "ScreenHandler.h"
#include "Subscreen.h"
#include "SDLUtility.h"

ScreenHandler::ScreenHandler()
{
	mousetoevaluate_ = NULL;
	previousmousevent_ = NULL;
	currentmouseevent_ = NULL;
	mouseevent_ = NO_MOUSE_STATE;
	ismousedown_ = false;

	demoscreen_ = new DemoScreen(22);
	demoscreen_->CreateCaption("In C++ there are conditional assignment situations where use of the if-else statement is impossible, since this language explicitly distinguishes between initialization and assignment. In such case it is always possible to use a function call, but this can be cumbersome and inelegant. For example, to pass conditionally different values as an argument for a constructor of a field or a base class, it is impossible to use a plain if-else statement; in this case we can use a conditional assignment expression, or a function call.",
		.15, .80, .70, 0);
	screens_.push_back(demoscreen_);

	int windowh = SDLUtility::GetScreenHeight();
	inputscreen_ = new InputScreen(SDL_Rect{ 0, 0, demoscreen_->GetScreenSize().x, windowh });
	screens_.push_back(inputscreen_);
	keyboardentry_.SetTexture(inputscreen_->GetTexture());

	currentcontextmenu_ = NULL;
	mousefunction_.Init(SDL_Rect{ 0, 0, SDLUtility::GetScreenWidth(), SDLUtility::GetScreenHeight() });

	backgroundimages_.push_back(new Image);
	backgroundimages_[0]->CreateTextureFromImage("blossom.png");
	backgroundimages_.push_back(new Image);
	backgroundimages_[1]->CreateTextureFromImage("orange.png");
	backgroundimage_ = 0;

	cmenu_.AddListItem(new UIButton(SDL_Rect{ 0, 0, ContextMenu::STANDARD_CONTEXT_MENU_WIDTH, ContextMenu::STANDARD_CONTEXT_MENU_HEIGHT }, "Violet Layout", true));
	cmenu_.AddListItem(new UIButton(SDL_Rect{ 0, 0, ContextMenu::STANDARD_CONTEXT_MENU_WIDTH, ContextMenu::STANDARD_CONTEXT_MENU_HEIGHT }, "Yellow-Red Layout", true));
	cmenu_.SetXY(0, 0);
}

ScreenHandler::~ScreenHandler()
{
	SetEntryTexture(NULL);

	delete demoscreen_;
	demoscreen_ = NULL;
	delete inputscreen_;
	inputscreen_ = NULL;

	screens_.clear();
}

void ScreenHandler::PreEventMouseSetup()
{
	previousmousevent_ = currentmouseevent_;

	if (ismousedown_ != true)
		mouseevent_ = MOUSEOVER;
}

void ScreenHandler::HandleEvents(const SDL_Event &e)
{

	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		ismousedown_ = true;
		mouseevent_ = e.button.button;

		if (currentcontextmenu_ != NULL)
		{
			if (currentcontextmenu_->CheckMouseHandlers() == NULL)
				SetContextMenu(NULL);
		}
	}

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		ismousedown_ = false;
		mouseevent_ = e.button.button;
	}

	if (e.type == SDL_KEYUP)
		keyboardentry_.KeyUpInput(e);

	if (e.type == SDL_KEYDOWN)
	{
		switch (keyboardentry_.KeyDownInput(e))
		{
		case (KeyboardEntry::DELETE_CAPTIONS) :
			if (demoscreen_ != NULL)
				demoscreen_->DeleteAllCaptions();
			break;
		case (KeyboardEntry::SET_TEXT_ENGLISH) :
			DebugText::CreateMessage("English Entry");
			break;
		case (KeyboardEntry::SET_TEXT_JAPANESE) :
			DebugText::CreateMessage("Japanese Entry");
			break;
		}
	}
}

void ScreenHandler::PostEventMouseSetup()
{
		currentmouseevent_ = &mousefunction_;

		for (std::list<Subscreen*>::iterator it = screens_.begin(); it != screens_.end(); it++)
		{
			mousetoevaluate_ = (*it)->CheckMouseHandlers(GetCurrentMouseState(mouseevent_, ismousedown_));

			if (mousetoevaluate_ != NULL)
			{
				currentmouseevent_ = mousetoevaluate_;
			}
		}

		if (currentcontextmenu_ != NULL)
		{
			mousetoevaluate_ = currentcontextmenu_->CheckMouseHandlers();
			if (mousetoevaluate_ != NULL)
			{
				currentmouseevent_ = mousetoevaluate_;
			}
		}

		if (previousmousevent_ != NULL && previousmousevent_ != currentmouseevent_)
		{
			if (ismousedown_ == true)
				currentmouseevent_ = previousmousevent_;
			else
				previousmousevent_->ResetMouseEvents();
		}

		if (currentmouseevent_ != NULL)
		{
			currentmouseevent_->SetEvent(GetCurrentMouseState(mouseevent_, ismousedown_));
		}
}

void ScreenHandler::ShowScreens()
{
	if (mousefunction_.GetEvent() == RIGHT_BUTTON_UP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		currentcontextmenu_ = &cmenu_;
		currentcontextmenu_->SetXY(x, y);
	}

	switch (cmenu_.GetButtonPress())
	{
	case UIElements::VIOLET_LAYOUT:
		UIElements::SetColorLayout(UIElements::VIOLET_LAYOUT);
		backgroundimage_ = UIElements::VIOLET_LAYOUT;
		break;
	case UIElements::YELLOW_RED_LAYOUT:
		UIElements::SetColorLayout(UIElements::YELLOW_RED_LAYOUT);
		backgroundimage_ = UIElements::YELLOW_RED_LAYOUT;
		break;
	}

	SDLUtility::PostImage(backgroundimages_[backgroundimage_], 0,	0, SDL_Rect{ 0, 0, backgroundimages_[backgroundimage_]->GetWidth(), backgroundimages_[backgroundimage_]->GetHeight() });

	if (inputscreen_ != NULL)
	{
		std::string currentstring;

		switch (inputscreen_->Show())
		{
		case InputScreen::SET_KEYBOARD_ENTRY:
			if (keyboardentry_.GetTexture() != inputscreen_->GetTexture())
				keyboardentry_.SetTexture(inputscreen_->GetTexture());
			break;
		case InputScreen::APPLY_BUTTON_PRESSED:
			if (keyboardentry_.GetTexture() == inputscreen_->GetTexture())
				keyboardentry_.FinalizeCurrentText();

			demoscreen_->SetCaptionText(inputscreen_->PostCurrentString(), -1);
			break;
		case InputScreen::RETURN_KEY_PRESSED:
			currentstring = inputscreen_->PostCurrentString();

			if (demoscreen_->GetSelectedCaptionText() != currentstring && currentstring != "")
				demoscreen_->SetCaptionText(currentstring, -1);
			break;
		case InputScreen::CLOSE_SCREEN:
			if (keyboardentry_.GetTexture() == inputscreen_->GetTexture())
				keyboardentry_.SetTexture(NULL);

			screens_.remove(inputscreen_);
			delete inputscreen_;
			inputscreen_ = NULL;
			break;
		}
	}

	if (demoscreen_->Show() == DemoScreen::GET_CONTEXT_MENU)
	{
		int dsmousex, dsmousey;
		SDL_GetMouseState(&dsmousex, &dsmousey);
		currentcontextmenu_ = demoscreen_->GetCurrentContextMenu();
		currentcontextmenu_->SetXY(dsmousex, dsmousey);
	}

	if (currentcontextmenu_ != NULL)
	{
		if (currentcontextmenu_->GetButtonPress() > -1)
			SetContextMenu(NULL);
		else
			currentcontextmenu_->ShowMenu();
	}
}

int ScreenHandler::GetCurrentMouseState(int mouseevent_, bool isdown)
{
	if (mouseevent_ == MOUSEOVER)
		return MOUSEOVER;

	if (isdown == true)
	{
		if (mouseevent_ == SDL_BUTTON_LEFT)
		{
			return LEFT_BUTTON_DOWN;
		}
		else
		{
			if (mouseevent_ == SDL_BUTTON_RIGHT)
				return RIGHT_BUTTON_DOWN;
		}
	}
	else
	{
		if (mouseevent_ == SDL_BUTTON_LEFT)
		{
			return LEFT_BUTTON_UP;
		}
		else
		{
			if (mouseevent_ == SDL_BUTTON_RIGHT)
				return RIGHT_BUTTON_UP;
		}
	}

	return NO_MOUSE_STATE;
}

void ScreenHandler::SetEntryTexture(TextInput *textinput)
{
	keyboardentry_.SetTexture(textinput);
}

void ScreenHandler::SetContextMenu(ContextMenu *contextmenu)
{
	if (currentcontextmenu_ != NULL)
		currentcontextmenu_->ResetMenu();

	currentcontextmenu_ = contextmenu;
}
