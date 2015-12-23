#include <list>
#include <string>

#include "SDL.h"

#include "ContextMenu.h"
#include "DebugText.h"
#include "DemoScreen.h"
#include "InputHandler.h"
#include "InputScreen.h"
#include "ScreenHandler.h"
#include "Subscreen.h"
#include "SDLUtility.h"

ScreenHandler::ScreenHandler()
{
	InputHandler::SetContextMenu(NULL);

	mousefunction_.Init(SDL_Rect{ 0, 0, SDLUtility::GetScreenWidth(), SDLUtility::GetScreenHeight() });
	InputHandler::AddMouseHandler(&mousefunction_);

	demoscreen_ = new DemoScreen(22);
	demoscreen_->CreateCaption("In C++ there are conditional assignment situations where use of the if-else statement is impossible, since this language explicitly distinguishes between initialization and assignment. In such case it is always possible to use a function call, but this can be cumbersome and inelegant. For example, to pass conditionally different values as an argument for a constructor of a field or a base class, it is impossible to use a plain if-else statement; in this case we can use a conditional assignment expression, or a function call.",
		.15, .80, .70, 0);
	screens_.push_back(demoscreen_);

	int windowh = SDLUtility::GetScreenHeight();
	inputscreen_ = new InputScreen(SDL_Rect{ 0, 0, demoscreen_->GetScreenSize().x, windowh });
	screens_.push_back(inputscreen_);
	InputHandler::SetKeyboardEntryTexture(inputscreen_->GetTexture());

	backgroundimages_.push_back(new Image);
	backgroundimages_[0]->CreateTextureFromImage("blossom.png");
	backgroundimages_.push_back(new Image);
	backgroundimages_[1]->CreateTextureFromImage("orange.png");
	backgroundimage_ = 0;

	cmenu_.AddListItem(new UIButton(SDL_Rect{ SDLUtility::GetScreenWidth(), 0, ContextMenu::STANDARD_CONTEXT_MENU_WIDTH, ContextMenu::STANDARD_CONTEXT_MENU_HEIGHT }, "Violet Layout", true));
	cmenu_.AddListItem(new UIButton(SDL_Rect{ SDLUtility::GetScreenWidth(), 0, ContextMenu::STANDARD_CONTEXT_MENU_WIDTH, ContextMenu::STANDARD_CONTEXT_MENU_HEIGHT }, "Yellow-Red Layout", true));
	cmenu_.SetXY(0, 0);
}

ScreenHandler::~ScreenHandler()
{
	InputHandler::RemoveMouseHandler(&mousefunction_);

	delete demoscreen_;
	demoscreen_ = NULL;
	delete inputscreen_;
	inputscreen_ = NULL;

	screens_.clear();
}

void ScreenHandler::ShowScreens(int macro)
{
	if (mousefunction_.GetEvent() == RIGHT_BUTTON_UP)
	{
		InputHandler::SetContextMenu(&cmenu_);
	}

	switch (cmenu_.GetButtonPress())
	{
	case UIElements::VIOLET_LAYOUT:
		UIElements::SetColorLayout(UIElements::VIOLET_LAYOUT);
		backgroundimage_ = UIElements::VIOLET_LAYOUT;
		InputHandler::SetContextMenu(NULL);
		break;
	case UIElements::YELLOW_RED_LAYOUT:
		UIElements::SetColorLayout(UIElements::YELLOW_RED_LAYOUT);
		backgroundimage_ = UIElements::YELLOW_RED_LAYOUT;
		InputHandler::SetContextMenu(NULL);
		break;
	}

	switch(macro)
	{
	case KeyboardEntry::DELETE_CAPTIONS:
		demoscreen_->DeleteAllCaptions();
		break;
	case KeyboardEntry::SET_TEXT_ENGLISH:
		DebugText::CreateMessage("English Text");
		break;
	case KeyboardEntry::SET_TEXT_JAPANESE:
		DebugText::CreateMessage("Japanese Text");
		break;
	case KeyboardEntry::TEXT_FINALIZED:
		InputHandler::SetKeyboardEntryTexture(NULL);
		break;
	}

	SDLUtility::PostImage(backgroundimages_[backgroundimage_], 0, 0, SDL_Rect{ 0, 0, backgroundimages_[backgroundimage_]->GetWidth(), backgroundimages_[backgroundimage_]->GetHeight() });

	if (inputscreen_ != NULL)
	{
		std::string currentstring;

		switch (inputscreen_->Show())
		{
		case InputScreen::APPLY_BUTTON_PRESSED:
			currentstring = inputscreen_->PostCurrentString();
			if (InputHandler::IsKeyboardEntryNull() == true)
				InputHandler::SetKeyboardEntryTexture(inputscreen_->GetTexture());

			if (demoscreen_->GetSelectedCaptionText() != currentstring && currentstring != "")
				demoscreen_->SetCaptionText(currentstring, -1);
			break;
		case InputScreen::RETURN_KEY_PRESSED:
			currentstring = inputscreen_->PostCurrentString();
			if (InputHandler::IsKeyboardEntryNull() == true)
				InputHandler::SetKeyboardEntryTexture(inputscreen_->GetTexture());

			if (demoscreen_->GetSelectedCaptionText() != currentstring && currentstring != "")
				demoscreen_->SetCaptionText(currentstring, -1);
			break;
		case InputScreen::CLOSE_SCREEN:
			InputHandler::SetKeyboardEntryTexture(NULL);

			screens_.remove(inputscreen_);
			delete inputscreen_;
			inputscreen_ = NULL;
			break;
		}
	}

	demoscreen_->Show();

	ContextMenu *currentcontextmenu = InputHandler::GetContextMenu();
	if (currentcontextmenu != NULL)
	{
		currentcontextmenu->ShowMenu();
	}
}
