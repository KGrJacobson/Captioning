#ifndef STORED_CAPTION_SCREEN
#define STORED_CAPTION_SCREEN

#include "SDL.h"

#include "StoredCaptionContainer.h"
#include "Subscreen.h"

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