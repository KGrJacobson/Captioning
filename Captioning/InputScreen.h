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
	InputScreen(SDL_Rect setscreenarea);
	~InputScreen();
	MouseHandler *CheckMouseHandlers(int mouseaction);
	void Show();
	void InsertCharacter(char character, bool isshift);
	void DeleteCharacter();
	void KeyboardInput(const SDL_Event &e, bool shift);
	std::string PostText();
private:
	SDL_Rect screenarea_;
	SDL_Rect textinputbox_;
	TextInput texttexture_;
	UIButton *confirmbutton_;
	UIButton *cancelbutton_;
	std::string currenttext_;
};

#endif //INPUT_SCREEN