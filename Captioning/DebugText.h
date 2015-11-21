 #pragma once
#include <iostream>
#include "TextInput.h"
#include <list>
#include <string>

static std::list<TextInput*> messagelist;

class DebugText
{
public:
	static void CreateMessage(std::string debugmessage);
	static void ClearMessages();
	static void PostMessages();
};