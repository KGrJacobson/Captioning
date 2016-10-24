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
#include "KWindow\MouseHandler.h"

StoredCaptionScreen::StoredCaptionScreen(SDL_Rect setscreenarea)
{
	screenarea_ = setscreenarea;

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

	int xoffset = 25;
	int yoffset = 0;

	for (int tabs = 0; tabs < captionlisttabs_.size(); ++tabs)
	{
		captionlisttabs_[tabs]->SetButtonCoordinates(screenarea_.x, screenarea_.y + yoffset);
		UIElements::ShowUIButton(captionlisttabs_[tabs]);
		if (captionlisttabs_[tabs]->GetMouseEvent() == 2)
		{
			currentcaptionlist_ = tabs;
		}
	}

	StoredCaptionContainer* currentlyselectioncaption = allcaptionlists_[currentcaptionlist_]->at(currentcaptionindex_[currentcaptionlist_]);

	if (currentcaptionindex_[currentcaptionlist_] >= 0 && currentlyselectioncaption->IsSelected() == false)
		currentlyselectioncaption->SetSelected();

	for (unsigned int captionlistindex = startonthisindex_; captionlistindex < allcaptionlists_[currentcaptionlist_]->size(); ++captionlistindex)
	{
		allcaptionlists_[currentcaptionlist_]->at(captionlistindex)->SetXY(screenarea_.x + xoffset, screenarea_.y + yoffset);

		if (allcaptionlists_[currentcaptionlist_]->at(captionlistindex)->IsSelected() == true && captionlistindex != currentcaptionindex_[currentcaptionlist_])
			allcaptionlists_[currentcaptionlist_]->at(captionlistindex)->SetSelected();

		if (allcaptionlists_[currentcaptionlist_]->at(captionlistindex)->Show() == StoredCaptionContainer::CAPTION_SELECTED)
		{
			if (captionlistindex != currentcaptionindex_[currentcaptionlist_])
			{
				if (currentcaptionindex_[currentcaptionlist_] >= 0)
					allcaptionlists_[currentcaptionlist_]->at(captionlistindex)->SetSelected();

				currentcaptionindex_[currentcaptionlist_] = captionlistindex;
				allcaptionlists_[currentcaptionlist_]->at(captionlistindex)->SetSelected();
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
	currentcaptionlist_ = 0;
	allcaptionlists_.clear();
	currentcaptionindex_.clear();
	captionlisttabs_.clear();
	int nextcaptionlisttoaddto = 0;

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

	int captionnumber = 0;

	//std::string name = " ";
	//std::string japanesedialogue = " ";
	//std::string englishdialogue = " ";

	//while (std::getline(file, newline))
	//{
	//	if (!newline.empty() && newline.compare("________________") != 0)
	//	{
	//		if (tempname_.count(newline) != 0)
	//		{
	//			name = tempname_[newline];

	//			std::getline(file, newline);
	//			japanesedialogue = newline;

	//			std::getline(file, newline);
	//			englishdialogue = newline;
	//		}
	//		else
	//		{
	//			std::vector<std::string> strings;

	//			while (!newline.empty() && newline.compare("________________") != 0)
	//			{
	//				strings.push_back(newline);
	//				std::getline(file, newline);
	//			}

	//			japanesedialogue = "";
	//			englishdialogue = "";

	//			for (int n = 0; n < strings.size() / 2; ++n)
	//			{
	//				japanesedialogue = japanesedialogue + "\n" + strings[n];
	//			}

	//			for (int m = strings.size() / 2; m < strings.size(); ++m)
	//			{
	//				if (m == strings.size() / 2)
	//					englishdialogue = englishdialogue + strings[m];
	//				else
	//					englishdialogue = englishdialogue + "\n" + strings[m];
	//			}
	//		}

	//		StoredCaptionContainer *newcaption = GetNewContainer(1);
	//		newcaption->SetText(1, "#" + std::to_string(captionnumber), japanesedialogue, englishdialogue);

	//		dialoguestruct *newdialogue;
	//		newdialogue = new dialoguestruct{ name, newcaption };

	//		dialoguelist_.push_back(newdialogue);

	//		dialoguelist_.back()->container->SetXY(screenarea_.x, yoffset);
	//		dialoguelist_.back()->container->SetMouse();

	//		name = " ";
	//		englishdialogue = " ";
	//		japanesedialogue = " ";
	//		++captionnumber;
	//	}


	//	if (newline.compare("________________") == 0)
	//	{
	//		name = " ";
	//		englishdialogue = " ";
	//		japanesedialogue = " ";

	//		StoredCaptionContainer *newcaption = GetNewContainer(1);
	//		newcaption->SetText(1, "#" + std::to_string(captionnumber), japanesedialogue, englishdialogue);

	//		dialoguestruct *newdialogue;
	//		newdialogue = new dialoguestruct{ name, newcaption };

	//		dialoguelist_.push_back(newdialogue);

	//		dialoguelist_.back()->container->SetXY(screenarea_.x, yoffset);
	//		dialoguelist_.back()->container->SetMouse();

	//		++captionnumber;
	//	}
	//}

	allcaptionlists_.push_back(new std::vector<StoredCaptionContainer*>);
	currentcaptionindex_.push_back(0);
	captionlisttabs_.push_back(new UIButton(SDL_Rect{ 0, 0, 25, StoredCaptionContainer::STANDARD_STORED_CONTAINER_HEIGHT }, "ST", UIElements::STANDARD_UI_FONT_SIZE, true));

	while (std::getline(file, newline))
	{
		if (!newline.empty() && newline.compare("________________") != 0)
		{
			std::vector<std::string> strings;

			if (tempname_.count(newline) != 0)
			{
				strings.push_back(tempname_[newline]);

				std::getline(file, newline);
				strings.push_back(newline);

				std::getline(file, newline);
				strings.push_back(newline);

				allcaptionlists_[nextcaptionlisttoaddto]->push_back(GetNameDialogueContainer(strings, captionnumber));
			}
			else
			{
				while (!newline.empty() && newline.compare("________________") != 0)
				{
					strings.push_back(newline);
					std::getline(file, newline);
				}

				allcaptionlists_[nextcaptionlisttoaddto]->push_back(GetDialogueContainer(strings, captionnumber));
			}

			++captionnumber;
		}
	}

	file.close();
}

StoredCaptionContainer * StoredCaptionScreen::GetCurrentDialogue(int index)
{
	startonthisindex_ = index - (index % 14);

	return allcaptionlists_[currentcaptionlist_]->at(index);
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
	if (currentcaptionindex_[currentcaptionlist_] != index)
		currentcaptionindex_[currentcaptionlist_] = index;
}

int StoredCaptionScreen::getcurrentindex()
{
	return currentcaptionindex_[currentcaptionlist_];
}

StoredCaptionContainer * StoredCaptionScreen::GetNameDialogueContainer(std::vector<std::string> &unprocesseddialogue, int captionnumber)
{
	int yoffset = 0;

	std::string name = unprocesseddialogue[0];
	std::string japanesedialogue = unprocesseddialogue[1];
	std::string englishdialogue = unprocesseddialogue[2];

	StoredCaptionContainer *newcaption = GetNewContainer(1);
	newcaption->SetText(1, "#" + std::to_string(captionnumber), japanesedialogue, name + '\n' + englishdialogue);
	newcaption->SetXY(screenarea_.x, yoffset);
	newcaption->SetMouse();

	return newcaption;
}

StoredCaptionContainer * StoredCaptionScreen::GetDialogueContainer(std::vector<std::string> &unprocesseddialogue, int captionnumber)
{
	int yoffset = 0;

	std::string japanesedialogue = "";
	std::string englishdialogue = "";

	for (int n = 0; n < unprocesseddialogue.size(); ++n)
	{
		if (n < unprocesseddialogue.size() / 2)
		{
			japanesedialogue = japanesedialogue + "\n" + unprocesseddialogue[n];
		}
		else
		{
			if (n == unprocesseddialogue.size() / 2)
				englishdialogue = englishdialogue + unprocesseddialogue[n];
			else
				englishdialogue = englishdialogue + "\n" + unprocesseddialogue[n];
		}
	}

	StoredCaptionContainer *newcaption = GetNewContainer(1);
	newcaption->SetText(1, "#" + std::to_string(captionnumber), japanesedialogue, englishdialogue);
	newcaption->SetXY(screenarea_.x, yoffset);
	newcaption->SetMouse();

	return newcaption;
}
