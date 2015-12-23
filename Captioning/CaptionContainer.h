#ifndef CAPTION_CONTAINER
#define CAPTION_CONTAINER

#include <list>
#include <string>

#include "SDL.h"

#include "MouseHandler.h"
#include "SDLUtility.h"
#include "TextInput.h"
#include "UIButton.h"
#include "UIElements.h"

const static int MINIMUM_HEIGHT_OF_CAPTION = 20;

enum captioncontainerflags
{
	DEFAULT,
	DELETE_CAPTION,
	SELECT_CAPTION,
	MOVE_CAPTION
};

class CaptionContainer
{
public:
	~CaptionContainer();
	void Init(std::string initialtext, double relativex, double relativey, double relativew, SDL_Rect destrect, int initialfontsize, int id);
	void SetText(std::string newtext, int destinationw);
	void SetXY(int x, int y);
	void EraseText();
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
	UIButton *deletebutton_;
	UIButton *movebutton_;
}; 

#endif //CAPTION_CONTAINER