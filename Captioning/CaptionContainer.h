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

//Caption_Container_Flags provides information to the Demo Screen to process the container when rendering its contents.
//NO_RETURN_CODE does nothing.
//DELETE_CAPTION is used when a user clicks on the "X" button on the caption and signals deletion of the container.
//SELECT_CAPTION is used when a user clicks on the container and signals the caption to be selected.
//MOVE_CAPTION is used when a user holds the "O" button and signals the captions position to be altered.
enum Caption_Container_Flags
{
	NO_RETURN_CODE,
	DELETE_CAPTION,
	SELECT_CAPTION,
	MOVE_CAPTION
};

//A Caption Container is an area of the Demo Screen that provides a preview of any new captions to be sent to OBS.  Containers
//are denoted by their ID number, which is denoted in the Init function of the class.  The ID may be any positive number, but
//cannot be repeated. The ID number "-1" is the only exception and is used for captions created during run time. Containers
//are stored relative to their size and position on the Demo screen, allowing the Demo Screen to be any size while leaving 
//every container in the same position.  Only the x position, y position, and width are stored in the container while the height 
//is increased based on number of lines the string is broken into to fit into the caption area.  Major functions of the container 
//include deletion, text erasure, and the ability to be moved around the Demo Screen at will.
class CaptionContainer
{
public:
	~CaptionContainer();
	void Init(std::string initialtext, double relativex, double relativey, double relativew, SDL_Rect destrect, int initialfontsize, int id);
	void SetText(std::string newtext);
	void SetXY(int x, int y);
	void EraseText();
	void DeselectCaption();
	void SelectCaption();
	int GetID();
	std::string GetText();
	int Show(bool showcontainer);
	void FitText(std::string texttofit);
	void RemoveMouseHandler();
	void AddMouseHandler();
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