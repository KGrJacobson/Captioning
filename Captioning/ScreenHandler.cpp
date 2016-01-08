#include <list>
#include <string>

#include "SDL.h"

#include "KWindow\UIMenu.h"
#include "KWindow\DebugText.h"
#include "DemoScreen.h"
#include "KWindow\InputHandler.h"
#include "InputScreen.h"
#include "ScreenHandler.h"
#include "KWindow\ShortenedText.h"
#include "StoredCaptionScreen.h"
#include "KWindow\Subscreen.h"
#include "KWindow\SDLUtility.h"

//Create subscreens, background images, menu bar menus, and context menu.
ScreenHandler::ScreenHandler()
{
	UIElements::SetMenu(NULL, NULL, NULL);

	//set up universal background mousefunction
	mousefunction_.Init(SDL_Rect{ 0, 0, SDLUtility::GetScreenWidth(), SDLUtility::GetScreenHeight() });
	InputHandler::AddMouseHandler(&mousefunction_);

	//demo screen
	demoscreen_ = new DemoScreen(22);
	demoscreen_->CreateCaption("In C++ there are conditional assignment situations where use of the if-else statement is impossible, since this language explicitly distinguishes between initialization and assignment. In such case it is always possible to use a function call, but this can be cumbersome and inelegant. For example, to pass conditionally different values as an argument for a constructor of a field or a base class, it is impossible to use a plain if-else statement; in this case we can use a conditional assignment expression, or a function call.",
		.15, .70, .70, 0);

	//preentered screen
	int windowh = SDLUtility::GetScreenHeight();
	storedcaptionscreen_ = new StoredCaptionScreen(SDL_Rect{ 0, 0 + UIElements::STANDARD_MENU_HEIGHT, demoscreen_->GetScreenSize().x, windowh });

	//manual entry screen
	inputscreen_ = new InputScreen(SDL_Rect{ 0, 0 + UIElements::STANDARD_MENU_HEIGHT, demoscreen_->GetScreenSize().x, windowh });

	//push back in order of Screens enum
	screens_.push_back(storedcaptionscreen_);
	screens_.push_back(inputscreen_);
	screens_.push_back(demoscreen_);

	leftscreen_ = PREENTRED_CAPTION_SCREEN;

	backgroundimages_.push_back(new Image);
	backgroundimages_[0]->CreateTextureFromImage("blossom.png");
	backgroundimages_.push_back(new Image);
	backgroundimages_[1]->CreateTextureFromImage("orange.png");
	backgroundimage_ = 0;

	menubuttonscreens_ = new UIButton(SDL_Rect{ 0, 0, UIElements::STANDARD_MENU_WIDTH, UIElements::STANDARD_MENU_HEIGHT }, "Screens", UIElements::STANDARD_UI_FONT_SIZE, true);
	menuscreens_ = new UIMenu(UIMenu::STANDARD_CONTEXT_MENU_WIDTH, UIMenu::STANDARD_CONTEXT_MENU_HEIGHT, UIElements::STANDARD_UI_FONT_SIZE);
	menuscreens_->SetSizeOfMenu(5);
	menuscreens_->RenameMenuIndex(0, "Stored Captions");
	menuscreens_->RenameMenuIndex(1, "Manual Entry");	
	menuscreens_->RenameMenuIndex(2, "menu 3");
	menuscreens_->RenameMenuIndex(3, "menu 4");	
	menuscreens_->RenameMenuIndex(4, "menu 5");

	cmenu_ = new UIMenu(UIMenu::STANDARD_CONTEXT_MENU_WIDTH, UIMenu::STANDARD_CONTEXT_MENU_HEIGHT, UIElements::STANDARD_UI_FONT_SIZE);
	cmenu_->SetSizeOfMenu(2);
	cmenu_->RenameMenuIndex(0, "Violet Layout");
	cmenu_->RenameMenuIndex(1, "Yellow-Red Layout");
}

ScreenHandler::~ScreenHandler()
{
	InputHandler::RemoveMouseHandler(&mousefunction_);

	delete menubuttonscreens_;
	menubuttonscreens_ = NULL;
	delete demoscreen_;
	demoscreen_ = NULL;
	delete storedcaptionscreen_;
	storedcaptionscreen_ = NULL;
	delete inputscreen_;
	inputscreen_ = NULL;

	screens_.clear();
}

//Call Show functions for all subscreens, context menu, menu bar, and hover text as well as handle return codes for each subscreen.
//macro is the key macro or lack thereof returned by KeyboardEntry.
void ScreenHandler::ShowScreens(int macro)
{
	//show background image
	SDLUtility::PostImage(backgroundimages_[backgroundimage_], 0, 0, SDL_Rect{ 0, 0, backgroundimages_[backgroundimage_]->GetWidth(), backgroundimages_[backgroundimage_]->GetHeight() });

	if (mousefunction_.GetEvent() == RIGHT_BUTTON_UP)
	{
		UIElements::SetMenu(cmenu_, NULL, NULL);
	}

	//show current screen in leftscreen_
	switch (menuscreens_->GetButtonPress())
	{
	case PREENTRED_CAPTION_SCREEN:
		leftscreen_ = PREENTRED_CAPTION_SCREEN;
		UIElements::SetMenu(NULL, NULL, NULL);
		break;
	case MANUAL_CAPTION_SCREEN:
		leftscreen_ = MANUAL_CAPTION_SCREEN;
		UIElements::SetMenu(NULL, NULL, NULL);
		break;
	}

	//check native context menu
	switch (cmenu_->GetButtonPress())
	{
	case UIElements::VIOLET_LAYOUT:
		UIElements::SetColorLayout(UIElements::VIOLET_LAYOUT);
		backgroundimage_ = UIElements::VIOLET_LAYOUT;
		UIElements::SetMenu(NULL, NULL, NULL);
		break;
	case UIElements::YELLOW_RED_LAYOUT:
		UIElements::SetColorLayout(UIElements::YELLOW_RED_LAYOUT);
		backgroundimage_ = UIElements::YELLOW_RED_LAYOUT;
		UIElements::SetMenu(NULL, NULL, NULL);
		break;
	}

	//handle key macros
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
		InputHandler::SetKeyboardEntryTexture(NULL, SDLUtility::GetScreenWidth(), 0);
		break;
	}

	if (leftscreen_ != NO_SCREEN)
	{
		switch (leftscreen_)
		{
		case PREENTRED_CAPTION_SCREEN:
			screens_[leftscreen_]->Show();
			break;
		case MANUAL_CAPTION_SCREEN:
			std::string currentstring;

			if (InputHandler::IsKeyboardEntryNull() == true)
			{
				SDL_Rect textarea = inputscreen_->GetTextArea();
				InputHandler::SetKeyboardEntryTexture(inputscreen_->GetTexture(), textarea.x, textarea.y + textarea.h);
			}

			switch (screens_[leftscreen_]->Show())
			{
			case InputScreen::APPLY_BUTTON_PRESSED:
				currentstring = inputscreen_->PostCurrentString();
				if (demoscreen_->GetSelectedCaptionText() != currentstring && currentstring != "")
					demoscreen_->SetCaptionText(currentstring, -1);
				break;
			case InputScreen::RETURN_KEY_PRESSED:
				currentstring = inputscreen_->PostCurrentString();
				if (demoscreen_->GetSelectedCaptionText() != currentstring && currentstring != "")
					demoscreen_->SetCaptionText(currentstring, -1);
				break;
			case InputScreen::CLOSE_SCREEN:
				leftscreen_ = NO_SCREEN;
				break;
			}
			break;
		}
	}

	demoscreen_->Show();

	//show menu bar on top of screens
	UIElements::ShowUIContextMenu(menubuttonscreens_);
	SDL_Rect menurect = menubuttonscreens_->GetButtonArea();
	int menux = menurect.x;
	int menuy = menurect.y + menurect.h;
	if (menubuttonscreens_->GetMouseEvent() == LEFT_BUTTON_UP)
		UIElements::SetMenu(menuscreens_, &menux, &menuy);

	//show menus on top of everything
	InputHandler::ShowKeyboardInputMenu();

	UIMenu *currentmenu = UIElements::GetMenu();
	if (currentmenu != NULL)
	{
		currentmenu->ShowMenu(-1);
	}

	//ShortenenedText *currenthovertext = UIElements::GetHoverText();
	//if (currenthovertext != NULL && currenthovertext->GetMouseEvent() != NO_MOUSE_STATE)
	//{
	//	currenthovertext->ShowFullHoverText();
	//}
	//else
	//{
	//	UIElements::SetHoverText(NULL);
	//}
}
