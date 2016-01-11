#include <fstream>
#include <string>

#include "SDL.h"

#include "KWindow\InputHandler.h"
#include "KWindow\MouseHandler.h"
#include "StoredCaptionContainer.h"
#include "StoredCaptionScreen.h"
#include "KWindow\UIElements.h"
#include "KWindow\UIMenu.h"

StoredCaptionScreen::StoredCaptionScreen(SDL_Rect setscreenarea)
{
	screenarea_ = setscreenarea;
	captions_.resize(1);
	captions_[0].resize(1);

	mousefunction_ = new MouseHandler;
	mousefunction_->SetMouseArea(setscreenarea);
	InputHandler::AddMouseHandler(mousefunction_);

	contextmenu_ = new UIMenu(UIMenu::STANDARD_CONTEXT_MENU_WIDTH, UIMenu::STANDARD_CONTEXT_MENU_HEIGHT, UIElements::STANDARD_UI_FONT_SIZE);
	contextmenu_->SetSizeOfMenu(2);
	contextmenu_->RenameMenuIndex(0, "Save File");
	contextmenu_->RenameMenuIndex(1, "Add New Caption List");

	captions_[0][0].push_back(GetNewContainer(0));
	captions_[0][0][0]->SetText(0, "nofile.txt", u8"同じ化", "A compound can be converted to a");
	
	captionpreview_.push_back(GetNewContainer(0));
	captionpreview_[0]->SetText(0, "nofile.txt", u8"同じ化", "A compound can be converted to a");

	captions_[0][0].push_back(GetNewContainer(1));
	captions_[0][0][1]->SetText(0, "nofile.txt", u8"成された、様々な違いから従来作とは全体的な雰囲気を異な", "was tens of thousands times more sensitive to");

	currentfile_ = "testtext.txt";
}

StoredCaptionScreen::~StoredCaptionScreen()
{
	delete contextmenu_;
	contextmenu_ = NULL;

	//for (std::vector<StoredCaptionContainer*>::iterator it = captions_.begin(); it != captions_.end(); ++it)
	//{
	//	delete (*it);
	//}
}

int StoredCaptionScreen::Show()
{
	int xoffset = 0;
	int yoffset = 0;
	int inneryoffset = 0;

	for (unsigned int captionlists = 0; captionlists < captions_.size(); ++captionlists)
	{
		xoffset = 0;
		inneryoffset = yoffset;
		captionpreview_[captionlists]->SetXY(screenarea_.x + xoffset, screenarea_.y + yoffset);
		captionpreview_[captionlists]->Show();

		for (unsigned int heldcaptions = 0; heldcaptions < captions_[captionlists].size(); ++heldcaptions)
		{
			xoffset = StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH;

			for (std::vector<StoredCaptionContainer*>::iterator appendedcaptions = captions_[captionlists][heldcaptions].begin(); appendedcaptions != captions_[captionlists][heldcaptions].end(); ++appendedcaptions)
			{
				(*appendedcaptions)->SetXY(screenarea_.x + xoffset, screenarea_.y + inneryoffset);
				(*appendedcaptions)->Show();

				xoffset += StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH;
			}

			inneryoffset += StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT;
		}

		yoffset += StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT;
	}

	if (mousefunction_->GetEvent() == RIGHT_BUTTON_UP)
	{
		UIElements::SetMenu(contextmenu_, NULL, NULL);
	}

	switch (contextmenu_->GetButtonPress())
	{
	case SAVE_FILE:
		SaveFile();
		UIElements::SetMenu(NULL, NULL, NULL);
		break;
	case ADD_NEW_CAPTION_LIST:
		captions_.resize(captions_.size() + 1);
		captions_.back().resize(1);
		captions_.back()[0].push_back(GetNewContainer(captions_.size()));
		captions_.back()[0][0]->SetText(captionpreview_.size(), "nofile.txt", "new caption", "new caption");

		captionpreview_.push_back(GetNewContainer(captionpreview_.size()));
		captionpreview_.back()->SetText(captionpreview_.size(), "nofile.txt", "new caption", "new caption");
		UIElements::SetMenu(NULL, NULL, NULL);
		break;
	}

	return 0;
}

StoredCaptionContainer *StoredCaptionScreen::GetNewContainer(int containerid)
{
	return new StoredCaptionContainer(SDL_Rect{ screenarea_.x, screenarea_.y, StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH, StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT }, containerid);
}

void StoredCaptionScreen::SaveFile()
{
	std::ofstream file;
	file.open(currentfile_, std::ios::out | std::ios::trunc);

	for (unsigned int captionlists = 0; captionlists < captions_.size(); ++captionlists)
	{
		file << "##newcaptionlist##\n";

		for (unsigned int heldcaptions = 0; heldcaptions < captions_[captionlists].size(); ++heldcaptions)
		{
			for (std::vector<StoredCaptionContainer*>::iterator appendedcaptions = captions_[captionlists][heldcaptions].begin(); appendedcaptions != captions_[captionlists][heldcaptions].end(); ++appendedcaptions)
			{
				file << (*appendedcaptions)->GetWriteData();

				if ((*appendedcaptions) != captions_[captionlists][heldcaptions].back())
					file << "\n+\n";
			}

			file << '\n';
		}
	}

	file << "##endoffile##";

	file.close();
}
