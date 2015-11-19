#include "DebugText.h"
#include <iostream>

void DebugText::Init()
{
	debugtexthandler.Init("meiryo.ttc", 12);
}

void DebugText::CreateMessage(std::string debugmessage)
{
	debugtexthandler.CreateTextureFromText(debugmessage, 0, 0);
}
