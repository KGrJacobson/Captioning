#ifndef STORED_CAPTION_CONTAINER
#define STORED_CAPTION_CONTAINER
#include <string>

#include "SDL.h"

#include "KWindow\UIMenu.h"
#include "KWindow\MouseHandler.h"
#include "KWindow\ShortenedText.h"

//A Stored Caption Container is very similar to the Demo Screens Caption Containers, but are associated
//with the Stored Caption Container screen and merely hold the text to be sent to the caption and the
//Caption Container ID it is associated with.  It is essentially one "half" of a Caption Container, with
//the other half being the position on the demo screen defined by the container ID.
class StoredCaptionContainer
{
public:
	static const int STANDARD_STORED_CONTAINER_WIDTH = 200;
	static const int STANDARD_STORED_CONTAINER_HEIGHT = 50;

	enum returncode
	{
		NO_RETURN_CODE,
		CAPTION_SELECTED,
		OPEN_EDIT_SCREEN
	};

	enum contextmenucode
	{
		EDIT_CAPTION
	};

	StoredCaptionContainer(SDL_Rect captionarea, int containernumber);
	~StoredCaptionContainer();
	void SetText(int captionid, std::string filein, std::string original, std::string translation);
	void SetArea(SDL_Rect newarea);
	int Show();
	int CheckFormattedTextMouse(ShortenenedText *text);
private:
	int captionid_;
	std::string containedinfile;
	ShortenenedText captioninfo_;
	ShortenenedText originaltext_;
	ShortenenedText translatedtext_;
	SDL_Rect captionarea_;
	int containernumber_;
	MouseHandler *mousefunction_;
	bool isselected_;
};

#endif //STORED_CAPTION_CONTAINER