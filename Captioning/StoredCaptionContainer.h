#ifndef STORED_CAPTION_CONTAINER
#define STORED_CAPTION_CONTAINER
#include <string>

#include "SDL.h"

#include "KWindow\MouseHandler.h"
#include "KWindow\ShortenedText.h"

class StoredCaptionContainer
{
public:
	static const int STANDARD_STORED_CONTAINER_WIDTH = 300;
	static const int STANDARD_STORED_CONTAINER_HEIGHT = 50;

	enum returncode
	{
		NO_RETURN_CODE,
		CAPTION_SELECTED
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