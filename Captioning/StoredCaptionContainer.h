#ifndef STORED_CAPTION_CONTAINER
#define STORED_CAPTION_CONTAINER
#include <string>

#include "SDL.h"

#include "MouseHandler.h"
#include "ShortenedText.h"

class StoredCaptionContainer
{
public:
	static const int STANDARD_STORED_CONTAINER_WIDTH = 300;
	static const int STANDARD_STORED_CONTAINER_HEIGHT = 60;

	enum returncode
	{
		NO_RETURN_CODE,
		CAPTION_SELECTED
	};

	StoredCaptionContainer(SDL_Rect captionarea, int containernumber);
	~StoredCaptionContainer();
	void SetText(int captionid, std::string filein, std::string original, std::string translation);
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
};

#endif //STORED_CAPTION_CONTAINER