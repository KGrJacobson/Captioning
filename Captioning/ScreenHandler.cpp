#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "SDL.h"

#include "KWindow\UIMenu.h"
#include "KWindow\DebugText.h"
#include "DemoScreen.h"
#include "KWindow\InputHandler.h"
#include "InputScreen.h"
#include "ScreenHandler.h"
#include "KWindow\ShortenedText.h"
#include "StoredCaptionContainer.h"
#include "StoredCaptionScreen.h"
#include "KWindow\Subscreen.h"
#include "KWindow\SDLUtility.h"

//Create subscreens, background images, menu bar menus, and context menu.
ScreenHandler::ScreenHandler()
{
	captionindex_ = -1;

	UIElements::SetMenu(NULL, NULL, NULL);

	//set up universal background mousefunction
	mousefunction_.Init(SDL_Rect{ 0, 0, SDLUtility::GetScreenWidth(), SDLUtility::GetScreenHeight() });
	InputHandler::AddMouseHandler(&mousefunction_);

	//demo screen
	demoscreen_ = new DemoScreen(22);

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
	menuscreens_->SetSizeOfMenu(2);
	menuscreens_->RenameMenuIndex(0, "Stored Captions");
	menuscreens_->RenameMenuIndex(1, "Manual Entry");

	std::ifstream captionfilelist;
	captionfilelist.open("P5/Documents.txt", std::ios::in);
	std::string newfile;

	while (std::getline(captionfilelist, newfile))
	{
		captionfiles_.push_back(newfile);
	}

	captionfilelist.close();

	menubuttonfiles_ = new UIButton(SDL_Rect{ UIElements::STANDARD_MENU_WIDTH, 0, UIElements::STANDARD_MENU_WIDTH, UIElements::STANDARD_MENU_HEIGHT }, "Files", UIElements::STANDARD_UI_FONT_SIZE, true);
	menufiles_ = new UIMenu(UIMenu::STANDARD_CONTEXT_MENU_WIDTH, UIMenu::STANDARD_CONTEXT_MENU_HEIGHT, UIElements::STANDARD_UI_FONT_SIZE);
	menufiles_->SetSizeOfMenu(captionfiles_.size());
	for (int files = 0; files < captionfiles_.size(); ++files)
	{
		menufiles_->RenameMenuIndex(files, captionfiles_[files]);
	}

	cmenu_ = new UIMenu(UIMenu::STANDARD_CONTEXT_MENU_WIDTH, UIMenu::STANDARD_CONTEXT_MENU_HEIGHT, UIElements::STANDARD_UI_FONT_SIZE);
	cmenu_->SetSizeOfMenu(2);
	cmenu_->RenameMenuIndex(0, "Violet Layout");
	cmenu_->RenameMenuIndex(1, "Yellow-Red Layout");
}

ScreenHandler::~ScreenHandler()
{
	demoscreen_->SetCaptionText(" ", 1);

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

	if (menufiles_->GetButtonPress() != UIMenu::NO_CONTEXT_MENU_BUTTONS_PRESSED)
	{
		storedcaptionscreen_->OpenFile("P5/" + captionfiles_[menufiles_->GetButtonPress()] + ".txt");
		UIElements::SetMenu(NULL, NULL, NULL);
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

	StoredCaptionContainer* newcaption;
	if (storedcaptionscreen_->getcurrentindex() != captionindex_)
	{
		captionindex_ = storedcaptionscreen_->getcurrentindex();

		if (captionindex_ >= 0)
		{
			newcaption = storedcaptionscreen_->GetCurrentDialogue(captionindex_);
			demoscreen_->SetCaptionText(newcaption->GetCaptionContents(), 1);
		}
		else
		{
			demoscreen_->SetCaptionText(" ", 1);
		}
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
	case KeyboardEntry::NEXT_CAPTION:
		storedcaptionscreen_->setcaptionindex(++captionindex_);

		newcaption = storedcaptionscreen_->GetCurrentDialogue(captionindex_);
		demoscreen_->SetCaptionText(newcaption->GetCaptionContents(), 1);
		break;
	case KeyboardEntry::PREVIOUS_CAPTION:
		storedcaptionscreen_->setcaptionindex(--captionindex_);

		newcaption = storedcaptionscreen_->GetCurrentDialogue(captionindex_);
		demoscreen_->SetCaptionText(newcaption->GetCaptionContents(), 1);
		break;
	case KeyboardEntry::RELOAD_CAPTION:
		newcaption = storedcaptionscreen_->GetCurrentDialogue(captionindex_);
		demoscreen_->SetCaptionText(newcaption->GetCaptionContents(), 1);
		break;
	case KeyboardEntry::NEXT_CAPTION_AND_EMPTY:
		storedcaptionscreen_->setcaptionindex(++captionindex_);
		demoscreen_->SetCaptionText(" ", 1);
		break;
	case KeyboardEntry::EMPTY_CAPTION:
		demoscreen_->SetCaptionText(" ", 1);
		break;
	case KeyboardEntry::PAGE_DOWN:
		storedcaptionscreen_->increaseindex();
		break;
	case KeyboardEntry::PAGE_UP:
		storedcaptionscreen_->decreaseindex();
		break;
	}

	if (leftscreen_ != NO_SCREEN)
	{
		switch (leftscreen_)
		{
		case PREENTRED_CAPTION_SCREEN:
			switch (screens_[leftscreen_]->Show())
			{
			case StoredCaptionScreen::ADD_NEW_CAPTION_LIST:
				std::vector<StoredCaptionContainer*> *listtoadd = storedcaptionscreen_->GetCaptionList();

				for (std::vector<StoredCaptionContainer*>::iterator it = (*listtoadd).begin(); it != (*listtoadd).end(); ++it)
				{
					if (demoscreen_->SetCaptionText((*it)->GetCaptionContents(), (*it)->GetContainerNumber()) == false)
					{
						RelativeRect newcontainer = storedcaptionscreen_->GetCaptionContainer((*it)->GetContainerNumber());

						demoscreen_->CreateCaption((*it)->GetCaptionContents(), newcontainer.x, newcontainer.y, newcontainer.w, (*it)->GetContainerNumber());
					}
				}
				break;
			}
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

	UIElements::ShowUIContextMenu(menubuttonfiles_);
	menurect = menubuttonfiles_->GetButtonArea();
	menux = menurect.x;
	menuy = menurect.y + menurect.h;
	if (menubuttonfiles_->GetMouseEvent() == LEFT_BUTTON_UP)
		UIElements::SetMenu(menufiles_, &menux, &menuy);

	//show menus on top of everything
	InputHandler::ShowKeyboardInputMenu();

	UIMenu *currentmenu = UIElements::GetMenu();
	if (currentmenu != NULL)
	{
		currentmenu->ShowMenu(-1);
	}

	ShortenenedText *currenthovertext = UIElements::GetHoverText();
	if (currenthovertext != NULL && currenthovertext->GetMouseEvent() != NO_MOUSE_STATE)
	{
		currenthovertext->ShowFullHoverText();
	}
	else
	{
		UIElements::SetHoverText(NULL);
	}
}
