#include "DebugText.h"
#include <iostream>
#include <list>
#include "SDLUtility.h"

void DebugText::CreateMessage(std::string debugmessage)
{
	TextInput *newmessage = new TextInput;
	newmessage->Init("meiryo.ttc", 12);
	newmessage->CreateTextureFromText(debugmessage);

	messagelist.push_back(newmessage);
}

void DebugText::ClearMessages()
{
	messagelist.erase(messagelist.begin(), messagelist.end());
}

void DebugText::PostMessages()
{
	int nexth = 0;

	for (std::list<TextInput*>::iterator it = messagelist.begin(); it != messagelist.end(); it++)
	{
		SDLUtility::PostText(*it, 0, nexth);

		nexth = nexth + (*it)->GetHeight();
	}
}
