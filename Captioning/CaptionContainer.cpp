#include "CaptionContainer.h"
#include "SDL.h"
#include "SDLUtility.h"
#include <list>
#include "DebugText.h"

CaptionContainer::~CaptionContainer()
{
	EraseText();
}

void CaptionContainer::Init(std::string initialtext, int initialx, int initialy, int initialw)
{
	text = initialtext;
	x = initialx;
	y = initialy;
	w = initialw;
	color = SDL_Color{ 255, 0, 255, 50 };
	FitText(initialtext);
}

void CaptionContainer::SetText(std::string newtext)
{
	EraseText();
	text = newtext;
	FitText(newtext);
}

void CaptionContainer::EraseText()
{
	texttextures.erase(texttextures.begin(), texttextures.end());
}

int CaptionContainer::GetX()
{
	return x;
}

int CaptionContainer::GetY()
{
	return y;
}

int CaptionContainer::GetW()
{
	return w;
}

std::string CaptionContainer::GetText()
{
	return text;
}

void CaptionContainer::ShowContainer()
{
	SDL_Rect containertoshow{ x, y, w, 200 };

	SDLUtility::CreateSquare(&containertoshow, &color);
}

void CaptionContainer::ShowCaption()
{
	int totalheight = 0;

	for (std::list<TextInput*>::reverse_iterator it = texttextures.rbegin(); it != texttextures.rend(); it++)
	{
		SDLUtility::PostText((*it), x, y + totalheight);
		totalheight = totalheight + (*it)->GetHeight();
	}
}

void CaptionContainer::FitText(std::string texttofit)
{
	std::string fittingtext;

	TextInput *newtext = new TextInput;
	newtext->Init("meiryo.ttc", 18);
	if (newtext->TextWidth(texttofit) > w)
	{
		fittingtext = texttofit.substr(0, (texttofit.length() * (static_cast<float>(w) / static_cast<float>(newtext->TextWidth(texttofit)))));

		if(texttofit.at(fittingtext.length()) != ' ')
			fittingtext = fittingtext.substr(0, fittingtext.find_last_of(" "));

		while (newtext->TextWidth(fittingtext) > w)
		{
			fittingtext = fittingtext.substr(0, fittingtext.find_last_of(" "));
		}

		FitText(texttofit.substr(fittingtext.length(), texttofit.length()));

		if (fittingtext.at(0) == ' ')
			fittingtext = fittingtext.substr(1, fittingtext.length());

		newtext->CreateTextureFromText(fittingtext);
		texttextures.push_back(newtext);
	} 
	else
	{
		fittingtext = texttofit;

		if (fittingtext.at(0) == ' ')
			fittingtext = fittingtext.substr(1, fittingtext.length());

		newtext->CreateTextureFromText(fittingtext);
		texttextures.push_back(newtext);
	}
}
