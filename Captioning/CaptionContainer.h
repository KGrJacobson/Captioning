#pragma once
#include <string>
#include <list>
#include "SDL.h"
#include "SDLUtility.h"
#include "TextInput.h"
#include "MouseHandler.h"

enum captioncontainerflags
{
	DEFAULT,
	DELETE_CAPTION,
	SELECT_CAPTION
};

class CaptionContainer
{
public:
	~CaptionContainer();
	void Init(std::string initialtext, float initialx, float initialy, float initialw, SDL_Rect destrect, int initialfontsize, int id);
	void SetText(std::string newtext, int destinationw);
	void EraseText();
	MouseHandler *CheckMouseEvents(int mouseevent);
	void DeselectCaption();
	void SelectCaption();
	int GetID();
	std::string GetText();
	int EvaluateCaption(bool showcontainer);
	void FitText(std::string texttofit, float destinationw);
private:
	std::string text;
	float x, y, w;
	int fontsize;
	int id;
	SDL_Rect absolutecoordinatesrect;
	SDL_Color color;
	std::list<TextInput*> texttextures;
	bool isselected;
	MouseHandler containermouseevent;
	MouseHandler deletebutton;
	MouseHandler selectbutton;
}; 