#ifndef SUBSCREEN
#define SUBSCREEN

#include "SDL.h"

#include "MouseHandler.h"

class Subscreen {
public:
	virtual MouseHandler *CheckMouseHandlers(int mouseaction) = 0;
	virtual int Show() = 0;
};

#endif //SUBSCREEN