#include <algorithm>
#include <list>

#include "SDL.h"

#include "CaptionContainer.h"
#include "DebugText.h"
#include "SDLUtility.h"

CaptionContainer::~CaptionContainer()
{
	EraseText();
}

void CaptionContainer::Init(std::string initialtext, float initialx, float initialy, float initialw, SDL_Rect destrect, int initialfontsize, int containerid)
{
	text_ = initialtext;
	x_ = initialx;
	y_ = initialy;
	w_ = initialw;
	fontsize_ = initialfontsize;
	id_ = containerid;
	isselected_ = false;
	color_ = SDL_Color{ 255, 0, 0, 50 };
	if (text_ != "")
		FitText(initialtext, (static_cast<float>(destrect.w)));

	absolutecoordinatesrect_ = SDL_Rect{ 
		static_cast<int>(destrect.x + (x_ * static_cast<float>(destrect.w))),
		static_cast<int>(destrect.y + (y_ * static_cast<float>(destrect.h))),
		static_cast<int>(w_ * static_cast<float>(destrect.w)),
		(texttextures_.size() != 0) ? static_cast<int>((*texttextures_.begin())->GetHeight() * texttextures_.size()) : 20
	};
	containermouseevent_.Init(absolutecoordinatesrect_.x, absolutecoordinatesrect_.y, absolutecoordinatesrect_.w, absolutecoordinatesrect_.h);
	deletebutton_.Init(absolutecoordinatesrect_.x, absolutecoordinatesrect_.y, 20, 20);
	selectbutton_.Init(absolutecoordinatesrect_.x + deletebutton_.GetMouseArea()->w, absolutecoordinatesrect_.y, 20, 20);
}

void CaptionContainer::SetText(std::string newtext, int destinationw)
{
	EraseText();
	text_ = newtext;
	if (text_ != "")
		FitText(text_, (static_cast<float>(destinationw)));

	absolutecoordinatesrect_.h = (texttextures_.size() != 0) ? std::max(static_cast<int>((*texttextures_.begin())->GetHeight() * texttextures_.size()), 20) : 20;
	containermouseevent_.SetMouseArea(absolutecoordinatesrect_.x, absolutecoordinatesrect_.y, absolutecoordinatesrect_.w, absolutecoordinatesrect_.h);
}

void CaptionContainer::EraseText()
{
	text_ = "";
	texttextures_.clear();
	absolutecoordinatesrect_.h = 20;
	containermouseevent_.SetMouseArea(absolutecoordinatesrect_.x, absolutecoordinatesrect_.y, absolutecoordinatesrect_.w, absolutecoordinatesrect_.h);
}

MouseHandler *CaptionContainer::CheckMouseEvents(int mouseevent)
{
	if (SDLUtility::IsMouseActive(containermouseevent_.GetMouseArea()))
	{
		if (SDLUtility::IsMouseActive(deletebutton_.GetMouseArea()))
			return &deletebutton_;

		if (SDLUtility::IsMouseActive(selectbutton_.GetMouseArea()))
			return &selectbutton_;

		return &containermouseevent_;
	}

	return NULL;
}

void CaptionContainer::DeselectCaption()
{
	isselected_ = false;
}

void CaptionContainer::SelectCaption()
{
	isselected_ = true;
}

int CaptionContainer::GetID()
{
	return id_;
}

std::string CaptionContainer::GetText()
{
	return text_;
}

int CaptionContainer::EvaluateCaption(bool showcontainer)
{
	int returncode = DEFAULT;
	int height = 20;
	if (texttextures_.size() != 0)
		height = std::max(static_cast<int>((*texttextures_.begin())->GetHeight() * texttextures_.size()), 20);

	SDL_Rect containerrect = absolutecoordinatesrect_;
	containerrect.h = height;

	if (showcontainer == true)
	{
		SDLUtility::CreateSquare(&containerrect, &color_);
	}

	if (text_ != "")
	{
		int totalheight = 0;
		containerrect.h = totalheight;

		for (std::list<TextInput*>::reverse_iterator it = texttextures_.rbegin(); it != texttextures_.rend(); it++)
		{
			SDLUtility::PostText((*it), containerrect.x, containerrect.y + totalheight);
			totalheight = totalheight + (*it)->GetHeight();
		}
	}

	switch (containermouseevent_.GetEvent())
	{
	case MOUSEOVER:
		deletebutton_.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton_.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_DOWN:
		deletebutton_.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton_.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_UP:
		returncode = SELECT_CAPTION;
		SelectCaption();
		break;
	}

	switch (deletebutton_.GetEvent())
	{
	case MOUSEOVER:
		deletebutton_.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton_.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_DOWN:
		deletebutton_.ShowMouseArea(SDL_Color{ 50, 0, 0, 255 });
		selectbutton_.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_UP:
		returncode = DELETE_CAPTION;
		break;
	}

	switch (selectbutton_.GetEvent())
	{
	case MOUSEOVER:
		deletebutton_.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton_.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_DOWN:
		deletebutton_.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton_.ShowMouseArea(SDL_Color{ 0, 50, 0, 255 });
		break;
	}

	if (isselected_ == true)
	{
		containermouseevent_.ShowMouseArea(SDL_Color{ 255, 255, 255, 35 });
	}

	return returncode;
}

void CaptionContainer::FitText(std::string texttofit, float destinationw)
{
	std::string fittingtext;
	int textboxwidth = w_ * destinationw;

	TextInput *newtext = new TextInput;
	newtext->Init("meiryo.ttc", fontsize_);
	if (newtext->TextWidth(texttofit) > textboxwidth)
	{
		fittingtext = texttofit.substr(0, (texttofit.length() * (textboxwidth / static_cast<float>(newtext->TextWidth(texttofit)))));

		if(texttofit.at(fittingtext.length()) != ' ')
			fittingtext = fittingtext.substr(0, fittingtext.find_last_of(" "));

		while (newtext->TextWidth(fittingtext) > textboxwidth)
		{
			fittingtext = fittingtext.substr(0, fittingtext.find_last_of(" "));
		}

		FitText(texttofit.substr(fittingtext.length(), texttofit.length()), destinationw);

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
