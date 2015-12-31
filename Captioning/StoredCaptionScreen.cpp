#include <iostream>
#include <string>

#include "SDL.h"

#include "StoredCaptionScreen.h"

StoredCaptionScreen::StoredCaptionScreen(SDL_Rect setscreenarea)
{
	screenarea_ = setscreenarea;
}

int StoredCaptionScreen::Show()
{
	return 0;
}
