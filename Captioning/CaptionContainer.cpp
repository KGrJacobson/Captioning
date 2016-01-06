#include <algorithm>
#include <list>

#include "SDL.h"

#include "CaptionContainer.h"
#include "KWindow\DebugText.h"
#include "KWindow\InputHandler.h"
#include "KWindow\SDLUtility.h"
#include "KWindow\UIElements.h"

CaptionContainer::~CaptionContainer()
{
	RemoveMouseHandler();

	EraseText();
	delete deletebutton_;
	deletebutton_ = NULL;
	delete movebutton_;
	movebutton_ = NULL;
}

//The Init function sets the values of the class members and allocates memory for the UI elements.
//Initialtext is a UTF8 string.  Passing a blank string ("") is possible.
//The x, y, and width values are a percentage of the Demo Screen and should be within 0.00 and 1.00 
//  (example : .50 would be half the width of the Demo Screen, or a coordinate halfway across the Demo Screen).
//Destrect is the area the Demo Screen occupies in the program.
//The font size is dependent on the current proportions of the Demo Screen similar to the x, y, and w values.
//The ID must be a positive number and not already used for another caption.  Containers created during runtime are the only exception to this.
void CaptionContainer::Init(std::string initialtext, double relativex, double relativey, double relativew, SDL_Rect destrect, int initialfontsize, int containerid)
{
	text_ = initialtext;
	relativecoordinatesrect_ = RelativeRect{ relativex, relativey, relativew, 0 };
	fontsize_ = initialfontsize;
	id_ = containerid;
	isselected_ = false;

	//Get the actual x, y coordinates of the container
	absolutecoordinatesrect_ = SDLUtility::GetAbsoluteRect(relativecoordinatesrect_, destrect);

	if (text_ != "")
		FitText(initialtext);

	//Get height of container, minimum height is a constant value decalared in the header file.
	absolutecoordinatesrect_.h = (texttextures_.size() != 0) ? static_cast<int>((*texttextures_.begin())->GetHeight() * texttextures_.size()) : MINIMUM_HEIGHT_OF_CAPTION;
	
	containermouseevent_.Init(absolutecoordinatesrect_);
	InputHandler::AddMouseHandler(&containermouseevent_);
	deletebutton_ = new UIButton(SDL_Rect{ absolutecoordinatesrect_.x, absolutecoordinatesrect_.y, 20, MINIMUM_HEIGHT_OF_CAPTION }, "X", UIElements::STANDARD_UI_FONT_SIZE, true);
	movebutton_ = new UIButton(SDL_Rect{ absolutecoordinatesrect_.x + 20, absolutecoordinatesrect_.y, 20, MINIMUM_HEIGHT_OF_CAPTION }, "O", UIElements::STANDARD_UI_FONT_SIZE, true);
}

//SetText alters the text inside the container and resizes the container to the appropriate height.
//newtext is a UTF8 string.  A blank string ("") is possible.
void CaptionContainer::SetText(std::string newtext)
{
	EraseText();
	text_ = newtext;
	if (text_ != "")
		FitText(text_);

	absolutecoordinatesrect_.h = (texttextures_.size() != 0) ? std::max(static_cast<int>((*texttextures_.begin())->GetHeight() * texttextures_.size()), MINIMUM_HEIGHT_OF_CAPTION) : MINIMUM_HEIGHT_OF_CAPTION;
	containermouseevent_.SetMouseArea(absolutecoordinatesrect_);
}

//SetXY alters the x and y coordinates of the container, usually to the current position of the mouse.
//This does not effect the relative coordinates of the container until sent to the client program and
//does not effect the positions of captions after the program ends.
void CaptionContainer::SetXY(int x, int y)
{
	absolutecoordinatesrect_.x = x - 30;
	absolutecoordinatesrect_.y = y - 10;

	containermouseevent_.SetMouseArea(absolutecoordinatesrect_);

	deletebutton_->SetButtonCoordinates(absolutecoordinatesrect_.x, absolutecoordinatesrect_.y);
	movebutton_->SetButtonCoordinates(absolutecoordinatesrect_.x + 20, absolutecoordinatesrect_.y);
}

//Erase text removes the contents of the container and resets it to default height.
void CaptionContainer::EraseText()
{
	text_ = "";
	texttextures_.clear();
	absolutecoordinatesrect_.h = MINIMUM_HEIGHT_OF_CAPTION;
	containermouseevent_.SetMouseArea(absolutecoordinatesrect_);
}

void CaptionContainer::DeselectCaption()
{
	isselected_ = false;
}

//Only one caption can be selected at any time.  The selected caption is the recipient of
//all new strings sent to the Demo Screen, whether created during the run time of the program
//or retrieved from files.
void CaptionContainer::SelectCaption()
{
	isselected_ = true;
}

int CaptionContainer::GetID()
{
	return id_;
}

//returns a UTF8 string of the text currently contained in the container.
std::string CaptionContainer::GetText()
{
	return text_;
}

//Show renders the caption and the move/delete buttons if the mouse is over the container on the 
//screen and returns an enum of any specific process that needs to be handled by the Demo Screen.
//See Caption_Container_Flags in the header file for details on the various return codes.
int CaptionContainer::Show(bool showcontainer)
{
	int returncode = NO_RETURN_CODE;
	int height = 20;
	if (texttextures_.size() != 0)
		height = std::max(static_cast<int>((*texttextures_.begin())->GetHeight() * texttextures_.size()), MINIMUM_HEIGHT_OF_CAPTION);

	SDL_Rect containerrect = absolutecoordinatesrect_;
	containerrect.h = height;

	if (showcontainer == true)
	{
		SDLUtility::CreateSquare(
			containerrect, 
			UIElements::GetUIElementColor(UIElements::CAPTION_CONTAINER_COLOR, UIElements::SEMITRANSPARENT_COLOR));
	}

	if (text_ != "")
	{
		int totalheight = 0;
		containerrect.h = totalheight;

		for (std::list<TextInput*>::reverse_iterator it = texttextures_.rbegin(); it != texttextures_.rend(); ++it)
		{
			SDLUtility::PostText((*it), containerrect.x, containerrect.y + totalheight);
			totalheight = totalheight + (*it)->GetHeight();
		}

		containerrect.h = totalheight;
	}

	if (isselected_ == true)
		containermouseevent_.ShowMouseArea(UIElements::GetUIElementColor(UIElements::CAPTION_CONTAINER_SELECTED_COLOR, UIElements::TRANSPARENT_COLOR));

	if (SDLUtility::IsMouseActive(containerrect) == true)
	{
		UIElements::ShowUITinyButton(deletebutton_);
		UIElements::ShowUITinyButton(movebutton_);
	}

	switch (containermouseevent_.GetEvent())
	{
	case LEFT_BUTTON_UP:
		returncode = SELECT_CAPTION;
		SelectCaption();
		break;
	}

	switch (deletebutton_->GetMouseEvent())
	{
	case LEFT_BUTTON_UP:
		returncode = DELETE_CAPTION;
		break;
	}

	switch (movebutton_->GetMouseEvent())
	{
	case LEFT_BUTTON_DOWN:
		returncode = MOVE_CAPTION;
		break;
	}

	return returncode;
}

//FitText recursively creates new textures to force the text to fit within the width
//of the conatiner.  The text is split on whitespaces with the first word to exceed the 
//width of the container becoming the first word of the next line and the whitespace is removed.
//If a single word of the text exceeds the alloted width of the container, the width is ignored
//and the entire word is posted as its own line.  If the text is smalled than the alloted width,
//only one texture is made.  This function works identically to the traditional "word wrap".
//texttofit is a UTF8 string
void CaptionContainer::FitText(std::string texttofit)
{
	std::string fittingtext;

	TextInput *newtext = new TextInput;
	newtext->Init(fontsize_);
	if (newtext->TextWidth(texttofit) > absolutecoordinatesrect_.w)
	{
		fittingtext = texttofit.substr(0, static_cast<int>((texttofit.length() * (absolutecoordinatesrect_.w / static_cast<double>(newtext->TextWidth(texttofit))))));

		if(texttofit.at(fittingtext.length()) != ' ')
			fittingtext = fittingtext.substr(0, fittingtext.find_last_of(" "));

		while (newtext->TextWidth(fittingtext) > absolutecoordinatesrect_.w)
		{
			fittingtext = fittingtext.substr(0, fittingtext.find_last_of(" "));
		}

		FitText(texttofit.substr(fittingtext.length(), texttofit.length()));

		if (fittingtext.at(0) == ' ')
			fittingtext = fittingtext.substr(1, fittingtext.length());

		newtext->CreateTextureFromText(fittingtext);
		texttextures_.push_back(newtext);
	} 
	else
	{
		fittingtext = texttofit;

		if (fittingtext.at(0) == ' ')
			fittingtext = fittingtext.substr(1, fittingtext.length());

		newtext->CreateTextureFromText(fittingtext);
		texttextures_.push_back(newtext);
	}
}

//Disable mouse interaction for this container
void CaptionContainer::RemoveMouseHandler()
{
	InputHandler::RemoveMouseHandler(&containermouseevent_);
	deletebutton_->RemoveMouseHandler();
	movebutton_->RemoveMouseHandler();
}

//Enable mouse interaction for this container.  MouseHandlers are enabled in the Init
//function of the container, so only use this function if RemoveMouseHandler has been
//called after the initialization of the container.
void CaptionContainer::AddMouseHandler()
{
	InputHandler::AddMouseHandler(&containermouseevent_);
	deletebutton_->SetMouseHandler();
	movebutton_->SetMouseHandler();
}
