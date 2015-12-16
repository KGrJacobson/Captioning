#ifndef CAPTION_CONTAINER
#define CAPTION_CONTAINER

#include <list>
#include <string>

#include "SDL.h"

#include "MouseHandler.h"
#include "SDLUtility.h"
#include "TextInput.h"

const static int MINIMUM_HEIGHT_OF_CAPTION = 20;

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
	void Init(std::string initialtext, double relativex, double relativey, double relativew, SDL_Rect destrect, int initialfontsize, int id);
	void SetText(std::string newtext, int destinationw);
	void EraseText();
	MouseHandler *CheckMouseEvents(int mouseevent);
	void DeselectCaption();
	void SelectCaption();
	int GetID();
	std::string GetText();
	int EvaluateCaption(bool showcontainer);
	void FitText(std::string texttofit);
private:
	std::string text_;
	RelativeRect relativecoordinatesrect_;
	SDL_Rect absolutecoordinatesrect_;
	int fontsize_;
	int id_;
	std::list<TextInput*> texttextures_;
	bool isselected_;
	MouseHandler containermouseevent_;
	MouseHandler deletebutton_;
	MouseHandler selectbutton_;
}; 

#endif //CAPTION_CONTAINER