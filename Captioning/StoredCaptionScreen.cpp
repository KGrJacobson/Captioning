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

	currentcaptionlistindex_ = -1;
	currentcaptionindex_ = -1;
	currentcaptionlist_ = NULL;
	currentcaption_ = NULL;
	returnlist_ = NULL;

	captioncontainers_ = std::vector<RelativeRect>{ RelativeRect{ .2, .8, .8, 0 }, RelativeRect{ .2, .73, .3, 0 } };

	mousefunction_ = new MouseHandler;
	mousefunction_->SetMouseArea(setscreenarea);
	InputHandler::AddMouseHandler(mousefunction_);

	contextmenu_ = new UIMenu(UIMenu::STANDARD_CONTEXT_MENU_WIDTH, UIMenu::STANDARD_CONTEXT_MENU_HEIGHT, UIElements::STANDARD_UI_FONT_SIZE);
	contextmenu_->SetSizeOfMenu(2);
	contextmenu_->RenameMenuIndex(0, "Save File");
	contextmenu_->RenameMenuIndex(1, "Add New Caption List");

	currentfile_ = "reminisceintro.txt";
	OpenFile(currentfile_);
}

StoredCaptionScreen::~StoredCaptionScreen()
{
	delete contextmenu_;
	contextmenu_ = NULL;

	//for (unsigned int captionlists = 0; captionlists < captions_.size(); ++captionlists)
	//{
	//	xoffset = 0;
	//	inneryoffset = yoffset;
	//	captionpreview_[captionlists]->SetXY(screenarea_.x + xoffset, screenarea_.y + yoffset);
	//	captionpreview_[captionlists]->Show();

	//	for (unsigned int heldcaptions = 0; heldcaptions < captions_[captionlists].size(); ++heldcaptions)
	//	{
	//		xoffset = StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH;

	//		for (std::vector<StoredCaptionContainer*>::iterator appendedcaptions = captions_[captionlists][heldcaptions].begin(); appendedcaptions != captions_[captionlists][heldcaptions].end(); ++appendedcaptions)
	//		{
	//			(*appendedcaptions)->SetXY(screenarea_.x + xoffset, screenarea_.y + inneryoffset);
	//			(*appendedcaptions)->Show();

	//			xoffset += StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH;
	//		}

	//		inneryoffset = inneryoffset + StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT;
	//	}

	//	yoffset += StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT;
	//}
}

int StoredCaptionScreen::Show()
{
	int returncode = NO_RETURN_CODE;

	int xoffset = 0;
	int yoffset = 0;
	int inneryoffset = 0;

	for (unsigned int captionlists = 0; captionlists < captions_.size(); ++captionlists)
	{
		xoffset = 0;
		inneryoffset = yoffset;
		captionpreview_[captionlists]->SetXY(screenarea_.x + xoffset, screenarea_.y + yoffset);
		switch (captionpreview_[captionlists]->Show())
		{
		case StoredCaptionContainer::CAPTION_SELECTED:
			if (currentcaptionlist_ != captionpreview_[captionlists])
			{
				if (currentcaptionlist_ != NULL)
				{
					currentcaptionlist_->SetSelected();
					for (unsigned int heldcaptions = 0; heldcaptions < captions_[currentcaptionlistindex_].size(); ++heldcaptions)
					{
						for (std::vector<StoredCaptionContainer*>::iterator appendedcaptions = captions_[captionlists][heldcaptions].begin(); appendedcaptions != captions_[captionlists][heldcaptions].end(); ++appendedcaptions)
						{
							(*appendedcaptions)->RemoveMouse();
						}
					}
				}

				if (currentcaption_ != NULL)
				{
					currentcaption_->SetSelected();
					currentcaption_ = NULL;
				}

				if (captionpreview_[captionlists]->SetSelected() == true)
				{
					currentcaptionlist_ = captionpreview_[captionlists];
					currentcaptionlistindex_ = captionlists;
				}
				else
				{
					currentcaptionlist_ = NULL;
				}

				for (unsigned int heldcaptions = 0; heldcaptions < captions_[captionlists].size(); ++heldcaptions)
				{
					xoffset = StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH;

					for (std::vector<StoredCaptionContainer*>::iterator appendedcaptions = captions_[captionlists][heldcaptions].begin(); appendedcaptions != captions_[captionlists][heldcaptions].end(); ++appendedcaptions)
					{
						(*appendedcaptions)->SetXY(screenarea_.x + xoffset, screenarea_.y + inneryoffset);
						(*appendedcaptions)->SetMouse();

						xoffset += StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH;
					}

					inneryoffset = inneryoffset + StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT;
				}

				xoffset = 0;
				inneryoffset = 0;
			}
			else
			{
				currentcaptionlist_->SetSelected();

				for (unsigned int heldcaptions = 0; heldcaptions < captions_[captionlists].size(); ++heldcaptions)
				{
					for (std::vector<StoredCaptionContainer*>::iterator appendedcaptions = captions_[captionlists][heldcaptions].begin(); appendedcaptions != captions_[captionlists][heldcaptions].end(); ++appendedcaptions)
					{
						(*appendedcaptions)->RemoveMouse();
					}
				}

				currentcaptionlist_ = NULL;
				if (currentcaption_ != NULL)
				{
					currentcaption_->SetSelected();
					currentcaption_ = NULL;
				}
			}
			break;
		}

		if (currentcaptionlist_ == captionpreview_[captionlists])
		{
			for (unsigned int heldcaptions = 0; heldcaptions < captions_[captionlists].size(); ++heldcaptions)
			{
				xoffset = StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH;

				for (std::vector<StoredCaptionContainer*>::iterator appendedcaptions = captions_[captionlists][heldcaptions].begin(); appendedcaptions != captions_[captionlists][heldcaptions].end(); ++appendedcaptions)
				{
					switch ((*appendedcaptions)->Show())
					{
					case StoredCaptionContainer::CAPTION_SELECTED:
						if ((*appendedcaptions) != currentcaption_)
						{
							std::vector<StoredCaptionContainer*>::iterator captionsandappended;

							if (currentcaption_ != NULL)
							{
								for (captionsandappended = captions_[captionlists][currentcaptionindex_].begin(); captionsandappended != captions_[captionlists][currentcaptionindex_].end(); ++captionsandappended)
								{
									(*captionsandappended)->SetSelected();
								}
							}

							currentcaption_ = (*appendedcaptions);
							
							for (captionsandappended = captions_[captionlists][heldcaptions].begin(); captionsandappended != captions_[captionlists][heldcaptions].end(); ++captionsandappended)
							{
								(*captionsandappended)->SetSelected();
							}
							currentcaptionindex_ = heldcaptions;
							returnlist_ = &captions_[captionlists][heldcaptions];
							returncode = ADD_NEW_CAPTION_LIST;
						}
						break;
					}

					xoffset += StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH;
				}

				inneryoffset = inneryoffset + StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT;
			}
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
		captions_.back()[0][0]->SetText(captionpreview_.size(), currentfile_, "new caption", "new caption");

		captionpreview_.push_back(GetNewContainer(captionpreview_.size()));
		captionpreview_.back()->SetText(captionpreview_.size(), currentfile_, "new caption", "new caption");
		captionpreview_.back()->SetMouse();
		UIElements::SetMenu(NULL, NULL, NULL);
		break;
	}

	return returncode;
}

StoredCaptionContainer *StoredCaptionScreen::GetNewContainer(int containerid)
{
	return new StoredCaptionContainer(SDL_Rect{ 0, 0, StoredCaptionContainer::STANDARD_STORED_CONTAINER_WIDTH, StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT }, containerid);
}

std::vector<StoredCaptionContainer*>* StoredCaptionScreen::GetCaptionList()
{
	return returnlist_;
}

RelativeRect StoredCaptionScreen::GetCaptionContainer(int containerindex)
{
	return captioncontainers_[containerindex];
}

void StoredCaptionScreen::SaveFile()
{
	std::ofstream file;
	file.open(currentfile_, std::ios::out | std::ios::trunc);

	file << "##startoffile## Introduction of the visual novel Reminisce (レミニセンス)\n";

	for (unsigned int captionlists = 0; captionlists < captions_.size(); ++captionlists)
	{
		file << "0\n";

		for (unsigned int heldcaptions = 0; heldcaptions < captions_[captionlists].size(); ++heldcaptions)
		{
			for (std::vector<StoredCaptionContainer*>::iterator appendedcaptions = captions_[captionlists][heldcaptions].begin(); appendedcaptions != captions_[captionlists][heldcaptions].end(); ++appendedcaptions)
			{
				file << (*appendedcaptions)->GetWriteData();

				if ((*appendedcaptions) != captions_[captionlists][heldcaptions].back())
					file << "\n2\n";
			}

			if (heldcaptions != captions_[captionlists].size())
				file << "\n1\n";
		}
	}

	file << "3\n";
	file << "##endoffile##";

	file.close();
}

void StoredCaptionScreen::OpenFile(std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ios::in);

	std::string newline;
	unsigned int currentid = 0;
	int yoffset = 0;

	int containerid = -1;
	std::string originaltext;
	std::string translatedtext;
	std::getline(file, newline);	//##startoffile##

	while (atoi(newline.c_str()) != END_FILE)
	{
		std::getline(file, newline);

		switch (atoi(newline.c_str()))
		{
		case NEW_CAPTION_LIST:
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
			captionpreview_.back()->SetXY(screenarea_.x, yoffset);
			captionpreview_.back()->SetMouse();

			yoffset += StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT;
			++currentid;
			break;
		case NEW_CAPTION_LIST_ELEMENT:
			captions_.back().resize(captions_.back().size() + 1);
			captions_.back().back().push_back(GetNewContainer(currentid));

			std::getline(file, newline);
			containerid = atoi(newline.c_str());

			std::getline(file, newline);
			originaltext = newline;

			std::getline(file, newline);
			translatedtext = newline;

			captions_.back().back()[0]->SetText(containerid, filename, originaltext, translatedtext);

			++currentid;
			break;
		case APPEND_CAPTION:
			captions_.back().back().push_back(GetNewContainer(currentid));

			std::getline(file, newline);
			containerid = atoi(newline.c_str());

			std::getline(file, newline);
			originaltext = newline;

			std::getline(file, newline);
			translatedtext = newline;

			captions_.back().back().back()->SetText(containerid, filename, originaltext, translatedtext);

			++currentid;
			break;
		}
	}

	file.close();
}
