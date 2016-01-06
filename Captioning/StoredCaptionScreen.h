#ifndef STORED_CAPTION_SCREEN
#define STORED_CAPTION_SCREEN

#include "SDL.h"

#include "StoredCaptionContainer.h"
#include "KWindow\Subscreen.h"

//Contains captions loaded from a given file to be sent to the Demo Screen when selected.
class StoredCaptionScreen : public Subscreen
{
public:
	StoredCaptionScreen(SDL_Rect setscreenarea);
	int Show();
private:
	SDL_Rect screenarea_;
	StoredCaptionContainer *testcaption_;
};

#endif //STORED_CAPTION_SCREEN