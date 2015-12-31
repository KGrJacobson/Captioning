#include <string>

#include "SDL.h"

#include "InputHandler.h"
#include "ShortenedText.h"
#include "TextInput.h"
#include "UIElements.h"

ShortenenedText::ShortenenedText()
{
	maxtextwidth_ = 0;
	mousefunction_ = new MouseHandler();
	mousefunction_->Init(SDL_Rect{ 0, 0, 0, 0 });
	InputHandler::AddMouseHandler(mousefunction_);
	fulltext_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);
}

ShortenenedText::~ShortenenedText()
{
	InputHandler::RemoveMouseHandler(mousefunction_);
	delete mousefunction_;
	mousefunction_ = NULL;
	isshortened_ = false;
}

void ShortenenedText::SetArea(SDL_Rect textarea)
{
	mousefunction_->SetMouseArea(textarea);

	if (textarea.w != maxtextwidth_)
	{
		maxtextwidth_ = textarea.w;
		CreateFittedText(GetCurrentText());
	}
}

void ShortenenedText::CreateFittedText(std::string text)
{
	int textwidth = TextWidth(text);

	std::string showtext;
	if (textwidth > maxtextwidth_)
	{
		double proportiontoshow = maxtextwidth_ / textwidth;
		showtext = text.substr(0, static_cast<int>(text.length() * proportiontoshow));
		if (showtext.length() >= 3)
		{
			showtext = showtext.substr(0, showtext.length() - 3);
			showtext = showtext + "...";
		}

		CreateTextureFromText(showtext);
		isshortened_ = true;
		fulltext_.CreateTextureFromText(text);
	}
	else
	{
		showtext = text;
		CreateTextureFromText(showtext);
		fulltext_.CreateTextureFromText(showtext);
	}

	SDL_Rect currentmousearea = mousefunction_->GetMouseArea();
	mousefunction_->SetMouseArea(SDL_Rect{ currentmousearea.x, currentmousearea.y, TextWidth(showtext), TextHeight() });
}

int ShortenenedText::GetMouseEvent()
{
	return mousefunction_->GetEvent();
}

void ShortenenedText::ShowFullHoverText()
{
	UIElements::ShowUIHoverText(&fulltext_);
}
