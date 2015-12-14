#ifndef DEBUG_TEXT
#define DEBUG_TEXT

#include <list>
#include <string>

#include "TextInput.h"

static std::list<TextInput*> messagelist;

class DebugText
{
public:
	static void CreateMessage(std::string debugmessage);
	static void CreateMessage(std::wstring debugmessage);
	static void ClearMessages();
	static void PostMessages();
};

#endif //DEBUG_TEXT