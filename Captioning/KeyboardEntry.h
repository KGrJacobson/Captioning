 #ifndef KEYBOARD_ENTRY
#define KEYBOARD_ENTRY

#include <string>

#include "TextInput.h"

class KeyboardEntry
{
public:
	KeyboardEntry();
	~KeyboardEntry();
	void InsertCharacter(char character);
	void DeleteCharacter();
	void SetTexture(TextInput *text);
	void SetShift(bool isdown);
	void SetCTRL(bool isdown);
	void FinalizeCurrentText();
	void KeyDownInput(const SDL_Event &e);
	void KeyUpInput(const SDL_Event &e);
	TextInput *GetTexture();
private:
	TextInput *currenttexttexture_;
	std::string currenttext_;
	bool isshift_;
	bool isctrl_;
};

#endif //KEYBOARD_ENTRY