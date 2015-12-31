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
	captionarea_ = captionarea;
	containernumber_ = containernumber;
	
	mousefunction_ = new MouseHandler();
	mousefunction_->Init(captionarea_);
	InputHandler::AddMouseHandler(mousefunction_);

	captioninfo_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);
	originaltext_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);
	translatedtext_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);
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

	//set text areas

	captioninfo_.CreateFittedText(std::to_string(captionid) + " " + filein);
	originaltext_.CreateFittedText(original);
	translatedtext_.CreateFittedText(translation);
}

int StoredCaptionContainer::Show()
{
	int returncode = NO_RETURN_CODE;

	if (mousefunction_->GetEvent() == LEFT_BUTTON_DOWN || captioninfo_.GetMouseEvent() == LEFT_BUTTON_DOWN ||
		originaltext_.GetMouseEvent() == LEFT_BUTTON_DOWN || translatedtext_.GetMouseEvent() == LEFT_BUTTON_DOWN)
	{

	}

	if (mousefunction_->GetEvent() == LEFT_BUTTON_UP || captioninfo_.GetMouseEvent() == LEFT_BUTTON_UP ||
		originaltext_.GetMouseEvent() == LEFT_BUTTON_UP || translatedtext_.GetMouseEvent() == LEFT_BUTTON_UP)
	{

	}

	if (mousefunction_->GetEvent() == RIGHT_BUTTON_UP || captioninfo_.GetMouseEvent() == RIGHT_BUTTON_UP ||
		originaltext_.GetMouseEvent() == RIGHT_BUTTON_UP || translatedtext_.GetMouseEvent() == RIGHT_BUTTON_UP)
	{

	}

	captioninfo_
	originaltext_
	translatedtext_

	return returncode;
}

int StoredCaptionContainer::CheckFormattedTextMouse(ShortenenedText *text)
{
	int mouseevent = text->GetMouseEvent();

	if (mouseevent == MOUSEOVER)
		text->ShowFullHoverText();

	return mouseevent;
}
