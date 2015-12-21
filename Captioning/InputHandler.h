#ifndef INPUT_HANDLER
#define INPUT_HANDLER
#include <list>

#include "SDL.h"

#include "ContextMenu.h"
#include "KeyboardEntry.h"
#include "MouseHandler.h"

namespace Input_Handler_Inputs
{
	KeyboardEntry *keyboardentry_ = NULL;
	ContextMenu *currentcontextmenu_ = NULL;
	MouseHandler *mousetoevaluate_ = NULL;
	MouseHandler *previousmousevent_ = NULL;
	MouseHandler *currentmouseevent_ = NULL;
	std::list<MouseHandler*> mouselist_;
}

class InputHandler
{
public:
	static void CloseInputs();
	static void AddMouseHandler(MouseHandler *mousehandler);
	static void RemoveMouseHandler(MouseHandler *mousehandler);
	static void CheckMouseHandlers();
	static void EvaluateMouseHandlers(int mouseaction);
	static void SetKeyboardEntry(KeyboardEntry *keyboardentry);
	static void SetContextMenu(ContextMenu *contextmenu);
};

#endif //INPUT_HANDLER