#include <list>
#include <string>

#include "DebugText.h"
#include "SDLUtility.h"

void DebugText::CreateMessage(std::string debugmessage)
{
	TextInput *newmessage = new TextInput;
	newmessage->Init("meiryo.ttc", 12);
	newmessage->CreateTextureFromText(debugmessage);

	messagelist.push_back(newmessage);
}

void DebugText::CreateMessage(std::wstring debugmessage)
{
	TextInput *newmessage = new TextInput;
	newmessage->Init("meiryo.ttc", 12);
	newmessage->CreateTextureFromText(debugmessage);

	messagelist.push_back(newmessage);
}

void DebugText::ClearMessages()
{
	messagelist.clear();
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
