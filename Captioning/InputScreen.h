#ifndef INPUT_SCREEN
#define INPUT_SCREEN

#include <list>
#include <string>

#include "SDL.h"

#include "CaptionContainer.h"
#include "KWindow\Image.h"
#include "KWindow\MouseHandler.h"
#include "KWindow\TextInput.h"
#include "KWindow\Subscreen.h"
#include "KWindow\UIButton.h"

static const int TEXT_INPUT_BOX_HEIGHT = 100;

//InputScreen is a "left screen" that allows a user to enter captions in a way similar to classic closed captioning works.The user 
//types in the caption and it is added to a selected container on the Demo Screen when the Apply button is pressed or the finalize text 
//key macro is pressed.If there is no currently selected caption, the text is discarded.
class InputScreen : public Subscreen
{
public:
	//Input_Screen_Return_Flags provides information to the Demo Screen to process the container when rendering its contents in Show.
	////NO_RETURN_CODE does nothing.
	//SET_KEYBOARD_ENTRY is used when the texttexture_ should be added to the instance of KeyboardEntry in InputHandler to receive user
	//  input.
	//APPLY_BUTTON_PRESSED is used when entering the data contained in texttexture_ to a selected container in the Demo Screen.
	//RETURN_KEY_PRESSED signals the same as APPLY_BUTTON_PRESSED, but notes that the input came from a key press, not the mouse.
	//CLOSE_SCREEN is used to close the Input Screen.
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
	int Show();
	std::string PostCurrentString();
	TextInput *GetTexture();
	SDL_Rect GetTextArea();
private:
	SDL_Rect screenarea_;
	TextInput texttexture_;
	MouseHandler textinputbox_;
	UIButton *confirmbutton_;
	UIButton *cancelbutton_;
};

#endif //INPUT_SCREEN