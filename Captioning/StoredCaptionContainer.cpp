#include "StoredCaptionContainer.h"
#include <string>

#include "SDL.h"

#include "InputHandler.h"
#include "MouseHandler.h"
#include "SDLUtility.h"
#include "ShortenedText.h"
#include "UIElements.h"

StoredCaptionContainer::StoredCaptionContainer(SDL_Rect captionarea, int containernumber)
{
	isselected_ = false;
	containernumber_ = containernumber;
	
	mousefunction_ = new MouseHandler();
	mousefunction_->Init(captionarea_);
	InputHandler::AddMouseHandler(mousefunction_);

	captioninfo_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);
	originaltext_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);
	translatedtext_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);

	captioninfo_.SetMouseActive();
	originaltext_.SetMouseActive();
	translatedtext_.SetMouseActive();

	SetArea(captionarea);
}

StoredCaptionContainer::~StoredCaptionContainer()
{
	InputHandler::RemoveMouseHandler(mousefunction_);
	delete mousefunction_;
	mousefunction_ = NULL;
}

void StoredCaptionContainer::SetText(int captionid, std::string filein, std::string original, std::string translation)
{
	captionid_ = captionid;

	captioninfo_.CreateFittedText(std::to_string(captionid) + " Box: " + std::to_string(containernumber_) + " " + filein);
	originaltext_.CreateFittedText(original);
	translatedtext_.CreateFittedText(translation);
}

void StoredCaptionContainer::SetArea(SDL_Rect newarea)
{
	captionarea_ = newarea;
	captioninfo_.SetArea(SDL_Rect{ captionarea_.x, captionarea_.y, captionarea_.w, captioninfo_.TextHeight() });
	originaltext_.SetArea(SDL_Rect{ captionarea_.x, captionarea_.y + captioninfo_.TextHeight(), captionarea_.w, originaltext_.TextHeight() });
	translatedtext_.SetArea(SDL_Rect{ captionarea_.x, captionarea_.y + captioninfo_.TextHeight() + originaltext_.TextHeight(), captionarea_.w, translatedtext_.TextHeight() });

	mousefunction_->SetMouseArea(newarea);
}

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
				//open context menu
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

	captioninfo_.Show();
	originaltext_.Show();
	translatedtext_.Show();

	return returncode;
}

int StoredCaptionContainer::CheckFormattedTextMouse(ShortenenedText *text)
{
	int mouseevent = text->GetMouseEvent();

	if (mouseevent == MOUSEOVER)
		InputHandler::SetHoverText(text);

	return mouseevent;
}
