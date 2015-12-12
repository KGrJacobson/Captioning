#include "CaptionContainer.h"
#include "SDL.h"
#include "SDLUtility.h"
#include <list>
#include "DebugText.h"

CaptionContainer::~CaptionContainer()
{
	EraseText();
}

void CaptionContainer::Init(std::string initialtext, float initialx, float initialy, float initialw, SDL_Rect destrect, int initialfontsize, int containerid)
{
	text = initialtext;
	x = initialx;
	y = initialy;
	w = initialw;
	fontsize = initialfontsize;
	id = containerid;
	isselected = false;
	color = SDL_Color{ 255, 0, 0, 50 };
	if (text != "")
		FitText(initialtext, (static_cast<float>(destrect.w)));

	absolutecoordinatesrect = SDL_Rect{ 
		static_cast<int>(destrect.x + (x * static_cast<float>(destrect.w))), 
		static_cast<int>(destrect.y + (y * static_cast<float>(destrect.h))),
		static_cast<int>(w * static_cast<float>(destrect.w)),
		(texttextures.size() != 0) ? static_cast<int>((*texttextures.begin())->GetHeight() * texttextures.size()) : 20
	};
	containermouseevent.Init(absolutecoordinatesrect.x, absolutecoordinatesrect.y, absolutecoordinatesrect.w, absolutecoordinatesrect.h);
	deletebutton.Init(absolutecoordinatesrect.x, absolutecoordinatesrect.y, 20, 20);
	selectbutton.Init(absolutecoordinatesrect.x + deletebutton.GetMouseArea()->w, absolutecoordinatesrect.y, 20, 20);
}

void CaptionContainer::SetText(std::string newtext, int destinationw)
{
	EraseText();
	text = newtext;
	if (text != "")
		FitText(text, (static_cast<float>(destinationw)));
}

void CaptionContainer::EraseText()
{
	text = "";
	texttextures.clear();
	absolutecoordinatesrect.h = 20;
	containermouseevent.SetMouseArea(absolutecoordinatesrect.x, absolutecoordinatesrect.y, absolutecoordinatesrect.w, absolutecoordinatesrect.h);
}

MouseHandler *CaptionContainer::CheckMouseEvents(int mouseevent)
{
	if (SDLUtility::IsMouseActive(containermouseevent.GetMouseArea()))
	{
		if (SDLUtility::IsMouseActive(deletebutton.GetMouseArea()))
			return &deletebutton;

		if (SDLUtility::IsMouseActive(selectbutton.GetMouseArea()))
			return &selectbutton;

		return &containermouseevent;
	}

	return NULL;
}

void CaptionContainer::DeselectCaption()
{
	isselected = false;
}

void CaptionContainer::SelectCaption()
{
	isselected = true;
}

int CaptionContainer::GetID()
{
	return id;
}

std::string CaptionContainer::GetText()
{
	return text;
}

int CaptionContainer::EvaluateCaption(bool showcontainer)
{
	int returncode = DEFAULT;
	int height = 20;
	if (texttextures.size() != 0)
		height = (*texttextures.begin())->GetHeight() * texttextures.size();

	SDL_Rect containerrect = absolutecoordinatesrect;
	containerrect.h = height;

	if (showcontainer == true)
	{
		SDLUtility::CreateSquare(&containerrect, &color);
	}

	if (text != "")
	{
		int totalheight = 0;
		containerrect.h = totalheight;

		for (std::list<TextInput*>::reverse_iterator it = texttextures.rbegin(); it != texttextures.rend(); it++)
		{
			SDLUtility::PostText((*it), containerrect.x, containerrect.y + totalheight);
			totalheight = totalheight + (*it)->GetHeight();
		}
	}

	switch (containermouseevent.GetEvent())
	{
	case MOUSEOVER:
		deletebutton.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_DOWN:
		deletebutton.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_UP:
		returncode = SELECT_CAPTION;
		SelectCaption();
		break;
	}

	switch (deletebutton.GetEvent())
	{
	case MOUSEOVER:
		deletebutton.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_DOWN:
		deletebutton.ShowMouseArea(SDL_Color{ 50, 0, 0, 255 });
		selectbutton.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_UP:
		returncode = DELETE_CAPTION;
		break;
	}

	switch (selectbutton.GetEvent())
	{
	case MOUSEOVER:
		deletebutton.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton.ShowMouseArea(SDL_Color{ 0, 150, 0, 255 });
		break;
	case LEFT_BUTTON_DOWN:
		deletebutton.ShowMouseArea(SDL_Color{ 150, 0, 0, 255 });
		selectbutton.ShowMouseArea(SDL_Color{ 0, 50, 0, 255 });
		break;
	}

	if (isselected == true)
	{
		containermouseevent.ShowMouseArea(SDL_Color{ 255, 255, 255, 35 });
	}

	return returncode;
}

void CaptionContainer::FitText(std::string texttofit, float destinationw)
{
	std::string fittingtext;
	int textboxwidth = w * destinationw;

	TextInput *newtext = new TextInput;
	newtext->Init("meiryo.ttc", fontsize);
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

		newtext->CreateTextureFromText(fittingtext, false);
		texttextures.push_back(newtext);
	} 
	else
	{
		fittingtext = texttofit;

		if (fittingtext.at(0) == ' ')
			fittingtext = fittingtext.substr(1, fittingtext.length());

		newtext->CreateTextureFromText(fittingtext, false);
		texttextures.push_back(newtext);
	}
}
