#pragma once
#include <list>
#include "MouseHandler.h"
#include "Subscreen.h"

class MouseEvaluator {
public:
	void Init(std::list<Subscreen*> *screenlist);
	void SetScreenList(std::list<Subscreen*> *screenlist);
	void CheckMouse(int mouseevent, bool isbuttondown);
private:
	std::list<Subscreen*> *activescreens;
	MouseHandler *previousmouse;
	MouseHandler *currentmouse;
	bool foundactive;
};