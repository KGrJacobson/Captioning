#include "CaptionContainer.h"
#include "SDL.h"
#include "SDLUtility.h"
#include <list>
#include "DebugText.h"

CaptionContainer::~CaptionContainer()
{
	EraseText();
}

void CaptionContainer::Init(std::string initialtext, float initialx, float initialy, float initialw, int destinationw, int initialfontsize, int containerid)
{
	text = initialtext;
	x = initialx;
	y = initialy;
	w = initialw;
	fontsize = initialfontsize;
	id = containerid;
	color = SDL_Color{ 255, 0, 0, 50 };
	FitText(initialtext, (static_cast<float>(destinationw)));
}

void CaptionContainer::SetText(std::string newtext, int destinationw)
{
	EraseText();
	text = newtext;
	FitText(newtext, (static_cast<float>(destinationw)));
}

void CaptionContainer::EraseText()
{
	texttextures.erase(texttextures.begin(), texttextures.end());
}

int CaptionContainer::GetID()
{
	return id;
}

std::string CaptionContainer::GetText()
{
	return text;
}

void CaptionContainer::ShowContainer(SDL_Rect destrect)
{
	SDL_Rect containertoshow{ destrect.x + (x * destrect.w), destrect.y + (y * destrect.h), w * destrect.w, .5 * destrect.h };

	SDLUtility::CreateSquare(&containertoshow, &color);
}

void CaptionContainer::ShowCaption(SDL_Rect destrect)
{
	int totalheight = 0;

	for (std::list<TextInput*>::reverse_iterator it = texttextures.rbegin(); it != texttextures.rend(); it++)
	{
		SDLUtility::PostText((*it), destrect.x + (x * destrect.w), destrect.y + (y * destrect.h) + totalheight);
		totalheight = totalheight + (*it)->GetHeight();
	}
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
