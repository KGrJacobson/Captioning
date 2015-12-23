#ifndef INPUT_HANDLER
#define INPUT_HANDLER
#include <list>

#include "SDL.h"

#include "ContextMenu.h"
#include "KeyboardEntry.h"
#include "MouseHandler.h"

namespace Input_Handler_Inputs
{
	static KeyboardEntry *keyboardentry_ = new KeyboardEntry();
	static ContextMenu *currentcontextmenu_ = NULL;
	static MouseHandler *mousetoevaluate_ = NULL;
	static MouseHandler *previousmousevent_ = NULL;
	static MouseHandler *currentmouseevent_ = NULL;
	static int mouseevent_ = NO_MOUSE_STATE;
	static bool ismousedown_ = false;
	static std::list<MouseHandler*> mouselist_;
}

class InputHandler
{
public:
	static void CloseInputs();
	static void AddMouseHandler(MouseHandler *mousehandler);
	static void RemoveMouseHandler(MouseHandler *mousehandler);
	static void CheckMouseHandlers();
	static int HandleEvents(const SDL_Event &e);
	static void SetKeyboardEntryTexture(TextInput *textinput);
	static bool IsKeyboardEntryNull();
	static void SetContextMenu(ContextMenu *contextmenu);
	static ContextMenu *GetContextMenu();
	static int GetCurrentMouseState(int mouseevent_, bool isdown);
};

#endif //INPUT_HANDLER