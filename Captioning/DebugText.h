#pragma once
#include <iostream>
#include "TextInput.h"

static TextInput debugtexthandler;

class DebugText
{
public:
	static void Init();
	static void CreateMessage(std::string debugmessage);
};