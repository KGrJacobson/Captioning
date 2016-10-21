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

	currentfile_ = "P5/P5Intro.txt";
	OpenFile(currentfile_);
}

StoredCaptionScreen::~StoredCaptionScreen()
{
	delete contextmenu_;
	contextmenu_ = NULL;
}

int StoredCaptionScreen::Show()
{
	int returncode = NO_RETURN_CODE;

	int xoffset = 0;
	int yoffset = 0;
	int inneryoffset = 0;

	if (currentcaptionindex_ >= 0 && dialoguelist_[currentcaptionindex_]->container->IsSelected() == false)
		dialoguelist_[currentcaptionindex_]->container->SetSelected();

	for (unsigned int dialoguelistindex = startonthisindex_; dialoguelistindex < dialoguelist_.size(); ++dialoguelistindex) 
	{
		dialoguelist_[dialoguelistindex]->container->SetXY(screenarea_.x + xoffset, screenarea_.y + yoffset);

		if (dialoguelist_[dialoguelistindex]->container->IsSelected() == true && dialoguelistindex != currentcaptionindex_)
			dialoguelist_[dialoguelistindex]->container->SetSelected();

		if (dialoguelist_[dialoguelistindex]->container->Show() == StoredCaptionContainer::CAPTION_SELECTED)
		{
			if (dialoguelistindex != currentcaptionindex_)
			{
				if (currentcaptionindex_ >= 0)
					dialoguelist_[dialoguelistindex]->container->SetSelected();

				currentcaptionindex_ = dialoguelistindex;
				dialoguelist_[dialoguelistindex]->container->SetSelected();
			}
		}

		yoffset += StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT;
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

void StoredCaptionScreen::OpenFile(std::string filename)
{
	startonthisindex_ = 0;
	currentcaptionindex_ = -1;
	dialoguelist_.clear();

	std::ifstream file;
	file.open(filename, std::ios::in);

	std::string newline;
	int yoffset = 0;

	int containerid = -1;

	//NAMES
	std::getline(file, newline);

	while (newline.compare("STORY DIALOGUE") != 0)
	{
		if (!newline.empty())
		{
			std::string japanese = newline;
			std::getline(file, newline);
			std::string english = newline;

			std::pair<std::string, std::string> name(japanese, english);

			tempname_.insert(name);
		}

		std::getline(file, newline);
	}

	std::string name = " ";
	std::string japanesedialogue = " ";
	std::string englishdialogue = " ";

	while (std::getline(file, newline))
	{
		if (newline.compare("________________") == 0)
		{
			name = " ";
			englishdialogue = " ";
			japanesedialogue = " ";

			StoredCaptionContainer *newcaption = GetNewContainer(1);
			newcaption->SetText(1, "nofile.txt", japanesedialogue, englishdialogue);

			dialoguestruct *newdialogue;
			newdialogue = new dialoguestruct{ name, newcaption };

			dialoguelist_.push_back(newdialogue);

			dialoguelist_.back()->container->SetXY(screenarea_.x, yoffset);
			dialoguelist_.back()->container->SetMouse();
		}
		else
		{
			if (!newline.empty())
			{
				if (tempname_.count(newline) != 0)
				{
					name = tempname_[newline];

					std::getline(file, newline);
					japanesedialogue = newline;

					std::getline(file, newline);
					englishdialogue = newline;
				}
				else
				{
					std::vector<std::string> strings;

					while (!newline.empty() && newline.compare("________________") != 0)
					{
						strings.push_back(newline);
						std::getline(file, newline);
					}

					if (newline.compare("________________") == 0)
					{
						name = " ";
						englishdialogue = " ";
						japanesedialogue = " ";

						StoredCaptionContainer *newcaption = GetNewContainer(1);
						newcaption->SetText(1, "nofile.txt", japanesedialogue, englishdialogue);

						dialoguestruct *newdialogue;
						newdialogue = new dialoguestruct{ name, newcaption };

						dialoguelist_.push_back(newdialogue);

						dialoguelist_.back()->container->SetXY(screenarea_.x, yoffset);
						dialoguelist_.back()->container->SetMouse();
					}

					japanesedialogue = "";
					englishdialogue = "";

					for (int n = 0; n < strings.size() / 2; ++n)
					{
						japanesedialogue = japanesedialogue + "\n" + strings[n];
					}

					for (int m = strings.size() / 2; m < strings.size(); ++m)
					{
						if (m == strings.size() / 2)
							englishdialogue = englishdialogue + strings[m];
						else
							englishdialogue = englishdialogue + "\n" + strings[m];
					}
				}

				StoredCaptionContainer *newcaption = GetNewContainer(1);
				newcaption->SetText(1, "nofile.txt", japanesedialogue, englishdialogue);

				dialoguestruct *newdialogue;
				newdialogue = new dialoguestruct{ name, newcaption };

				dialoguelist_.push_back(newdialogue);

				dialoguelist_.back()->container->SetXY(screenarea_.x, yoffset);
				dialoguelist_.back()->container->SetMouse();

				name = " ";
				englishdialogue = " ";
				japanesedialogue = " ";
			}
		}
	}

	file.close();
}

dialoguestruct * StoredCaptionScreen::GetCurrentDialogue(int index)
{
	startonthisindex_ = index - (index % 14);

	return dialoguelist_[index];
}

void StoredCaptionScreen::increaseindex()
{
	startonthisindex_ = startonthisindex_ + 14;
}

void StoredCaptionScreen::decreaseindex()
{
	startonthisindex_ = startonthisindex_ - 14;
}

void StoredCaptionScreen::setcaptionindex(int index)
{
	if (currentcaptionindex_ != index)
		currentcaptionindex_ = index;
}

int StoredCaptionScreen::getcurrentindex()
{
	return currentcaptionindex_;
}
