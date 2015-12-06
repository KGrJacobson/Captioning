#pragma once
#include <list>
#include "MouseHandler.h"

class MouseEvaluator {
public:
	void Init();

private:
	std::list<MouseHandler*> activemice;
	MouseHandler *previousmouse;
	MouseHandler *currentmouse;
	int mouseevent;
	bool ismousedown;
	bool foundactive;
};