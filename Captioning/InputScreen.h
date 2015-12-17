#ifndef INPUT_SCREEN
#define INPUT_SCREEN

#include <list>
#include <string>

#include "SDL.h"

#include "CaptionContainer.h"
#include "Image.h"
#include "MouseHandler.h"
#include "TextInput.h"
#include "Subscreen.h"
#include "UIButton.h"

static const int TEXT_INPUT_BOX_HEIGHT = 100;

class InputScreen : public Subscreen
{
public:
	enum Input_Screen_Return_Flags 
	{
		NO_RETURN_EVENT,
		SET_KEYBOARD_ENTRY,
		APPLY_BUTTON_PRESSED,
		RETURN_KEY_PRESSED,
		CLOSE_SCREEN
	};

	InputScreen(SDL_Rect setscreenarea);
	~InputScreen();
	MouseHandler *CheckMouseHandlers(int mouseaction);
	int Show();
	std::string PostCurrentString();
	TextInput *GetTexture();
private:
	SDL_Rect screenarea_;
	TextInput texttexture_;
	MouseHandler textinputbox_;
	UIButton *confirmbutton_;
	UIButton *cancelbutton_;
};

#endif //INPUT_SCREEN