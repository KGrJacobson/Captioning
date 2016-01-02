#ifndef INPUT_HANDLER
#define INPUT_HANDLER
#include <list>

#include "SDL.h"

#include "UIMenu.h"
#include "KeyboardEntry.h"
#include "MouseHandler.h"
#include "ShortenedText.h"
#include "TextInput.h"

namespace Input_Handler_Inputs
{
	static KeyboardEntry *keyboardentry_ = new KeyboardEntry();
	static UIMenu *currentmenu_ = NULL;
	static ShortenenedText *hovertext_ = NULL;
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
	static void SetMenu(UIMenu *contextmenu, int *x, int *y);
	static void SetHoverText(ShortenenedText *text);
	static UIMenu *GetMenu();
	static ShortenenedText *GetHoverText();
	static int GetCurrentMouseState(int mouseevent_, bool isdown);
};

#endif //INPUT_HANDLER