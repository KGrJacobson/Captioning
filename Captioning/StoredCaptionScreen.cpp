#include <iostream>
#include <fstream>
#include <stdlib.h>
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

	mousefunction_ = new MouseHandler;
	mousefunction_->SetMouseArea(setscreenarea);
	InputHandler::AddMouseHandler(mousefunction_);

	contextmenu_ = new UIMenu(UIMenu::STANDARD_CONTEXT_MENU_WIDTH, UIMenu::STANDARD_CONTEXT_MENU_HEIGHT, UIElements::STANDARD_UI_FONT_SIZE);
	contextmenu_->SetSizeOfMenu(2);
	contextmenu_->RenameMenuIndex(0, "Save File");
	contextmenu_->RenameMenuIndex(1, "Add New Caption List");

	currentfile_ = "testtext.txt";
	OpenFile(currentfile_);
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

	file << "##startoffile##\n";

	for (unsigned int captionlists = 0; captionlists < captions_.size(); ++captionlists)
	{
		file << "##newcaptionlist##\n";

		for (unsigned int heldcaptions = 0; heldcaptions < captions_[captionlists].size(); ++heldcaptions)
		{
			for (std::vector<StoredCaptionContainer*>::iterator appendedcaptions = captions_[captionlists][heldcaptions].begin(); appendedcaptions != captions_[captionlists][heldcaptions].end(); ++appendedcaptions)
			{
				file << (*appendedcaptions)->GetWriteData();

				if ((*appendedcaptions) != captions_[captionlists][heldcaptions].back())
					file << "\n##append##\n";
			}

			if (heldcaptions != captions_[captionlists].size())
				file << "\n##addcaptiontolist##\n";
		}
	}

	file << "##endoffile##";

	file.close();
}

void StoredCaptionScreen::OpenFile(std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ios::in);

	std::string newline;
	unsigned int currentid = 0;

	int containerid = -1;
	std::string originaltext;
	std::string translatedtext;

	while (newline != "##endoffile##")
	{
		std::getline(file, newline);

		if (newline == "##newcaptionlist##")
		{
			captions_.resize(captions_.size() + 1);
			captions_.back().resize(1);
			captions_.back()[0].push_back(GetNewContainer(currentid));

			captionpreview_.push_back(GetNewContainer(currentid));

			std::getline(file, newline);
			containerid = atoi(newline.c_str());

			std::getline(file, newline);
			originaltext = newline;

			std::getline(file, newline);
			translatedtext = newline;

			captions_.back()[0][0]->SetText(containerid, filename, originaltext, translatedtext);
			captionpreview_.back()->SetText(containerid, filename, originaltext, translatedtext);
			
			++currentid;
		}

		if (newline == "##addcaptiontolist##")
		{
			captions_.back().resize(captions_.size() + 1);
			captions_.back().back().push_back(GetNewContainer(currentid));

			std::getline(file, newline);
			containerid = atoi(newline.c_str());

			std::getline(file, newline);
			originaltext = newline;

			std::getline(file, newline);
			translatedtext = newline;

			captions_.back().back()[0]->SetText(containerid, filename, originaltext, translatedtext);

			++currentid;
		}

		if (newline == "##append##")
		{

			captions_.back().back().push_back(GetNewContainer(currentid));

			std::getline(file, newline);
			containerid = atoi(newline.c_str());

			std::getline(file, newline);
			originaltext = newline;

			std::getline(file, newline);
			translatedtext = newline;

			captions_.back().back().back()->SetText(containerid, filename, originaltext, translatedtext);

			++currentid;
		}
	}

	file.close();
}
