#include <list>
#include <string>

#include "SDL.h"

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

	backgroundimage_.CreateTextureFromImage("blossom.png");
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
	}

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		ismousedown_ = false;
		mouseevent_ = e.button.button;
	}

	if (e.type == SDL_KEYUP)
		keyboardentry_.KeyUpInput(e);

	if (e.type == SDL_KEYDOWN)
		keyboardentry_.KeyDownInput(e);
}

void ScreenHandler::PostEventMouseSetup()
{
		currentmouseevent_ = NULL;

		for (std::list<Subscreen*>::iterator it = screens_.begin(); it != screens_.end(); it++)
		{
			mousetoevaluate_ = (*it)->CheckMouseHandlers(GetCurrentMouseState(mouseevent_, ismousedown_));

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
	SDLUtility::PostImage(&backgroundimage_, 0,	0, SDL_Rect{ 0, 0, backgroundimage_.GetWidth(), backgroundimage_.GetHeight() });

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

	demoscreen_->Show();
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