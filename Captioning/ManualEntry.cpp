#include "ManualEntry.h"
#include "Image.h"
#include "SDLUtility.h"
#include <string>
#include <list>
#include <iostream>
#include "SDL.h"
#include "DebugText.h"

ManualEntry::ManualEntry()
{
	charimage.CreateTextureFromImage("ctext.png");
	textcolor = SDL_Color{ 255, 255, 255, 255 };
}

void ManualEntry::InsertCharacter(char character, bool isshift)
{
	if (character >= 'a' && character <= 'z' && isshift == true)
	{
		textentry.push_back(character - 32);
	}
	else
	{
		textentry.push_back(character);
	}
}

void ManualEntry::DeleteCharacter()
{
	if (textentry.empty() != true)
		textentry.pop_back();
}

int ManualEntry::TranslateCharacter(char character)
{
	if (character >= 'a' && character <= 'z')
	{
		return (character - 97 + 26) * 8;
	}

	if (character >= 'A' && character <= 'Z')
	{
		return (character - 65) * 8;
	}

	return 0;
}

void ManualEntry::PostCurrentEntry(int x, int y)
{
	int nextletterx = 0;
	SDL_Rect sourcerect{ 0, 0, 8, 9 };

	for (std::list<char>::iterator it = textentry.begin(); it != textentry.end(); it++)
	{
		if (*it != ' ')
		{
			sourcerect.x = TranslateCharacter(*it);

			SDLUtility::PostImage(&charimage, x + nextletterx, y, &sourcerect);
			nextletterx = nextletterx + 8;
		}
		else
		{
			nextletterx = nextletterx + 8;
		}
	}

	SDL_Rect cursorrect{ nextletterx + x, y, sourcerect.w, sourcerect.h };
	SDLUtility::CreateSquare(&cursorrect, &textcolor);
}

void ManualEntry::CreateString()
{
	std::string newstring;

	for (std::list<char>::iterator it = textentry.begin(); it != textentry.end(); it++)
	{
		newstring = newstring + (*it);
	}

	DebugText::CreateMessage(newstring);
	textentry.erase(textentry.begin(), textentry.end());
}

void ManualEntry::KeyboardInput(SDL_Event *e, bool shift)
{
	switch (e->key.keysym.sym) 
	{
	case SDLK_RETURN:
		CreateString();
		break;
	case SDLK_BACKSPACE:
		DeleteCharacter();
		break;
	case SDLK_SPACE:
		InsertCharacter(' ', shift);
		break;
	case SDLK_a:
		InsertCharacter('a', shift);
		break;
	case SDLK_b:
		InsertCharacter('b', shift);
		break;
	case SDLK_c:
		InsertCharacter('c', shift);
		break;
	case SDLK_d:
		InsertCharacter('d', shift);
		break;
	case SDLK_e:
		InsertCharacter('e', shift);
		break;
	case SDLK_f:
		InsertCharacter('f', shift);
		break;
	case SDLK_g:
		InsertCharacter('g', shift);
		break;
	case SDLK_h:
		InsertCharacter('h', shift);
		break;
	case SDLK_i:
		InsertCharacter('i', shift);
		break;
	case SDLK_j:
		InsertCharacter('j', shift);
		break;
	case SDLK_k:
		InsertCharacter('k', shift);
		break;
	case SDLK_l:
		InsertCharacter('l', shift);
		break;
	case SDLK_m:
		InsertCharacter('m', shift);
		break;
	case SDLK_n:
		InsertCharacter('n', shift);
		break;
	case SDLK_o:
		InsertCharacter('o', shift);
		break;
	case SDLK_p:
		InsertCharacter('p', shift);
		break;
	case SDLK_q:
		InsertCharacter('q', shift);
		break;
	case SDLK_r:
		InsertCharacter('r', shift);
		break;
	case SDLK_s:
		InsertCharacter('s', shift);
		break;
	case SDLK_t:
		InsertCharacter('t', shift);
		break;
	case SDLK_u:
		InsertCharacter('u', shift);
		break;
	case SDLK_v:
		InsertCharacter('v', shift);
		break;
	case SDLK_w:
		InsertCharacter('w', shift);
		break;
	case SDLK_x:
		InsertCharacter('x', shift);
		break;
	case SDLK_y:
		InsertCharacter('y', shift);
		break;
	case SDLK_z:
		InsertCharacter('z', shift);
		break;
	}
}
