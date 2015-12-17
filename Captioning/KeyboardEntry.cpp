#include <string>

#include "SDL.h"

#include "KeyboardEntry.h"
#include "TextInput.h"

KeyboardEntry::KeyboardEntry()
{
	isshift_ = false;
	isctrl_ = false;
}

KeyboardEntry::~KeyboardEntry()
{
	if (currenttexttexture_ != NULL)
	{
		FinalizeCurrentText();
		currenttexttexture_ = NULL;
	}

	currenttext_ = "";
}

void KeyboardEntry::InsertCharacter(char character)
{
	if (character >= 'a' && character <= 'z' && isshift_ == true)
	{
		currenttext_ = currenttext_ + static_cast<char>(character - 32);
	}
	else
	{
		currenttext_ = currenttext_ + character;
	}

	if (currenttexttexture_ != NULL)
		currenttexttexture_->CreateQuickTextureFromText(currenttext_);
}

void KeyboardEntry::DeleteCharacter()
{
	if (currenttext_ != "")
	{
		currenttext_.pop_back();
		if (currenttexttexture_ != NULL)
			currenttexttexture_->CreateQuickTextureFromText(currenttext_);
	}
}

void KeyboardEntry::SetTexture(TextInput *text)
{
	FinalizeCurrentText();

	currenttexttexture_ = text;
}

void KeyboardEntry::SetShift(bool isdown)
{
	isshift_ = isdown;
}

void KeyboardEntry::SetCTRL(bool isdown)
{
	isctrl_ = isdown;
}

void KeyboardEntry::FinalizeCurrentText()
{
	if (currenttexttexture_ != NULL)
		currenttexttexture_->CreateTextureFromText(currenttext_);

	currenttext_ = "";
}

void KeyboardEntry::KeyDownInput(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_BACKSPACE:
		DeleteCharacter();
		break;
	case SDLK_SPACE:
		InsertCharacter(' ');
		break;
	case SDLK_PERIOD:
		InsertCharacter('.');
		break;
	case SDLK_a:
		InsertCharacter('a');
		break;
	case SDLK_b:
		InsertCharacter('b');
		break;
	case SDLK_c:
		InsertCharacter('c');
		break;
	case SDLK_d:
		InsertCharacter('d');
		break;
	case SDLK_e:
		InsertCharacter('e');
		break;
	case SDLK_f:
		InsertCharacter('f');
		break;
	case SDLK_g:
		InsertCharacter('g');
		break;
	case SDLK_h:
		InsertCharacter('h');
		break;
	case SDLK_i:
		InsertCharacter('i');
		break;
	case SDLK_j:
		InsertCharacter('j');
		break;
	case SDLK_k:
		InsertCharacter('k');
		break;
	case SDLK_l:
		InsertCharacter('l');
		break;
	case SDLK_m:
		InsertCharacter('m');
		break;
	case SDLK_n:
		InsertCharacter('n');
		break;
	case SDLK_o:
		InsertCharacter('o');
		break;
	case SDLK_p:
		InsertCharacter('p');
		break;
	case SDLK_q:
		InsertCharacter('q');
		break;
	case SDLK_r:
		InsertCharacter('r');
		break;
	case SDLK_s:
		InsertCharacter('s');
		break;
	case SDLK_t:
		InsertCharacter('t');
		break;
	case SDLK_u:
		InsertCharacter('u');
		break;
	case SDLK_v:
		InsertCharacter('v');
		break;
	case SDLK_w:
		InsertCharacter('w');
		break;
	case SDLK_x:
		InsertCharacter('x');
		break;
	case SDLK_y:
		InsertCharacter('y');
		break;
	case SDLK_z:
		InsertCharacter('z');
		break;
	case SDLK_LSHIFT:
		SetShift(true);
		break;
	case SDLK_RSHIFT:
		SetShift(true);
		break;
	case SDLK_LCTRL:
		SetCTRL(true);
		break;
	case SDLK_RCTRL:
		SetCTRL(true);
		break;
	case SDLK_RETURN:
		FinalizeCurrentText();
		break;
	}
}

void KeyboardEntry::KeyUpInput(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LSHIFT:
		SetShift(false);
		break;
	case SDLK_RSHIFT:
		SetShift(false);
		break;
	case SDLK_LCTRL:
		SetCTRL(false);
		break;
	case SDLK_RCTRL:
		SetCTRL(false);
		break;
	}
}

TextInput *KeyboardEntry::GetTexture()
{
	return currenttexttexture_;
}
