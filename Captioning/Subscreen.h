#pragma once
#include <list>
#include <SDL.h>
#include "MouseHandler.h"

class Subscreen {
public:
	virtual void BuildMouseList() = 0;
	virtual MouseHandler *CheckMouseHandlers(int mouseaction) = 0;
	virtual void Show() = 0;
};