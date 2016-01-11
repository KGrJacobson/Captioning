#include "StoredCaptionContainer.h"
#include <string>

#include "SDL.h"

#include "KWindow\InputHandler.h"
#include "KWindow\MouseHandler.h"
#include "KWindow\SDLUtility.h"
#include "KWindow\ShortenedText.h"
#include "KWindow\UIButton.h"
#include "KWindow\UIElements.h"

//Initialize caption area, create context menu, and set MouseHandler as active.
//captionarea is the area the caption is rendered to.
//containernumber is the ID the caption is associated with.  When seleted the translatedtext_
//  will be added to the container with the matching ID in the Demo Screen.
StoredCaptionContainer::StoredCaptionContainer(SDL_Rect captionarea, int containernumber)
{
	isselected_ = false;
	containernumber_ = containernumber;
	
	mousefunction_ = new MouseHandler();
	mousefunction_->Init(captionarea_);
	InputHandler::AddMouseHandler(mousefunction_);

	captioninfo_.Init(UIElements::STANDARD_UI_FONT_SIZE);
	originaltext_.Init(UIElements::STANDARD_UI_FONT_SIZE);
	translatedtext_.Init(UIElements::STANDARD_UI_FONT_SIZE);

	captioninfo_.SetMouseActive();
	originaltext_.SetMouseActive();
	translatedtext_.SetMouseActive();

	SetArea(captionarea);

	contextmenu_ = new UIMenu(UIMenu::STANDARD_CONTEXT_MENU_WIDTH, UIMenu::STANDARD_CONTEXT_MENU_HEIGHT, UIElements::STANDARD_UI_FONT_SIZE);
	contextmenu_->SetSizeOfMenu(1);
	contextmenu_->RenameMenuIndex(0, "Edit Caption");
}

StoredCaptionContainer::~StoredCaptionContainer()
{
	delete contextmenu_;
	contextmenu_ = NULL;

	InputHandler::RemoveMouseHandler(mousefunction_);
	delete mousefunction_;
	mousefunction_ = NULL;
}

//Change the containers text.
//captionid is the Demo Screen container ID the caption is associated with.  See Demo Screen
//  for more details.
//filein is the file that the caption information is stored in.
//original is the original, untranslated text of the caption.
//translation is the translation of original.
void StoredCaptionContainer::SetText(int captionid, std::string filein, std::string original, std::string translation)
{
	captionid_ = captionid;

	captioninfo_.CreateFittedText(std::to_string(captionid) + " Box: " + std::to_string(containernumber_) + " " + filein);
	originaltext_.CreateFittedText(original);
	translatedtext_.CreateFittedText(translation);
}

//Set the area the container will be rendered to.
void StoredCaptionContainer::SetArea(SDL_Rect newarea)
{
	captionarea_ = newarea;
	captioninfo_.SetArea(SDL_Rect{ captionarea_.x, captionarea_.y, captionarea_.w, captioninfo_.TextHeight() });
	originaltext_.SetArea(SDL_Rect{ captionarea_.x, captionarea_.y + captioninfo_.TextHeight(), captionarea_.w, originaltext_.TextHeight() });
	translatedtext_.SetArea(SDL_Rect{ captionarea_.x, captionarea_.y + captioninfo_.TextHeight() + originaltext_.TextHeight(), captionarea_.w, translatedtext_.TextHeight() });

	mousefunction_->SetMouseArea(captionarea_);
}

void StoredCaptionContainer::SetXY(int x, int y)
{
	if (x != captionarea_.x || y != captionarea_.y)
	{
		captionarea_ = SDL_Rect{ x, y, captionarea_.w, captionarea_.h };
		captioninfo_.SetArea(SDL_Rect{ captionarea_.x, captionarea_.y, captionarea_.w, captioninfo_.TextHeight() });
		originaltext_.SetArea(SDL_Rect{ captionarea_.x, captionarea_.y + captioninfo_.TextHeight(), captionarea_.w, originaltext_.TextHeight() });
		translatedtext_.SetArea(SDL_Rect{ captionarea_.x, captionarea_.y + captioninfo_.TextHeight() + originaltext_.TextHeight(), captionarea_.w, translatedtext_.TextHeight() });

		mousefunction_->SetMouseArea(captionarea_);
	}
}

//Show renders the container on screen and returns a return code providing information
//on potentially altering the container.  See the StoredCaptionContainer header for
//more information on the return codes.
int StoredCaptionContainer::Show()
{
	int returncode = NO_RETURN_CODE;

	if (mousefunction_->GetEvent() == LEFT_BUTTON_DOWN || CheckFormattedTextMouse(&captioninfo_) == LEFT_BUTTON_DOWN ||
		CheckFormattedTextMouse(&originaltext_) == LEFT_BUTTON_DOWN || CheckFormattedTextMouse(&translatedtext_) == LEFT_BUTTON_DOWN)
	{
		SDLUtility::CreateBorderedRect(captionarea_, 
			UIElements::GetUIElementColor(UIElements::OUTLINED_BOX_COLOR, UIElements::SOLID_COLOR),
			UIElements::GetUIElementColor(UIElements::CAPTION_CONTAINER_COLOR, UIElements::SOLID_COLOR));
	}
	else
	{

		if (mousefunction_->GetEvent() == LEFT_BUTTON_UP || captioninfo_.GetMouseEvent() == LEFT_BUTTON_UP ||
			originaltext_.GetMouseEvent() == LEFT_BUTTON_UP || translatedtext_.GetMouseEvent() == LEFT_BUTTON_UP)
		{
			(isselected_ == false) ? isselected_ = true : isselected_ = false;
			returncode = CAPTION_SELECTED;
		}
		else
		{

			if (mousefunction_->GetEvent() == RIGHT_BUTTON_UP || captioninfo_.GetMouseEvent() == RIGHT_BUTTON_UP ||
				originaltext_.GetMouseEvent() == RIGHT_BUTTON_UP || translatedtext_.GetMouseEvent() == RIGHT_BUTTON_UP)
			{
				UIElements::SetMenu(contextmenu_, NULL, NULL);
			}
		}

		if (isselected_ == true)
		{
			SDLUtility::CreateBorderedRect(captionarea_,
				UIElements::GetUIElementColor(UIElements::OUTLINED_BOX_COLOR, UIElements::SOLID_COLOR),
				UIElements::GetUIElementColor(UIElements::CAPTION_CONTAINER_SELECTED_COLOR, UIElements::TRANSPARENT_COLOR));
		}
		else
		{
			SDLUtility::CreateBorderedRect(captionarea_,
				UIElements::GetUIElementColor(UIElements::OUTLINED_BOX_COLOR, UIElements::SOLID_COLOR),
				UIElements::GetUIElementColor(UIElements::CAPTION_CONTAINER_COLOR, UIElements::SEMITRANSPARENT_COLOR));
		}
	}

	switch (contextmenu_->GetButtonPress())
	{
	case EDIT_CAPTION:
		returncode = EDIT_CAPTION;
		UIElements::SetMenu(NULL, NULL, NULL);
		break;
	}

	captioninfo_.Show();
	originaltext_.Show();
	translatedtext_.Show();

	return returncode;
}

//Show hovertext for the container if necessary.  Used internally in Show.
int StoredCaptionContainer::CheckFormattedTextMouse(ShortenenedText *text)
{
	int mouseevent = text->GetMouseEvent();

	if (mouseevent == MOUSEOVER)
		UIElements::SetHoverText(text);

	return mouseevent;
}

std::string StoredCaptionContainer::GetWriteData()
{
	return std::to_string(containernumber_) + '\n' + originaltext_.GetFullText() + '\n' + translatedtext_.GetFullText();
}
