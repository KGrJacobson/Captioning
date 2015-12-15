#include <string>
#include <vector>

#include "SDL.h"

#include "TextInput.h"
#include "SDLUtility.h"
#include "UIElements.h"

void UIElements::Init()
{
	standardcolorvector_ = std::vector<SDL_Color>{
		SDL_Color{ 23, 20, 18, 255 },		//BLACK
		SDL_Color{ 235, 246, 247, 255 },	//WHITE
		SDL_Color{ 135, 95, 154, 255 },		//WISTERIA_PURPLE
		SDL_Color{ 151, 110, 154, 255 },	//TATARIAN_ASTER
		SDL_Color{ 43, 32, 40, 255 },		//BLUE_VIOLET
		SDL_Color{ 168, 124, 160, 255 },	//THIN_COLOR
		SDL_Color{ 91, 50, 86, 255 },		//VIOLET
		SDL_Color{ 35, 25, 30, 255 },		//DARK_RED
		SDL_Color{ 187, 119, 150, 255 },	//RED_WISTERIA
		SDL_Color{ 117, 93, 91, 255 },		//DOVE_FEATHER_GREY
		SDL_Color{ 109, 43, 80, 255 },		//VINE_GRAPE
		SDL_Color{ 164, 52, 93, 255 },		//TREE_PEONY
		SDL_Color{ 67, 36, 42, 255 },		//FAKE_PURPLE
		SDL_Color{ 126, 38, 57, 255 },		//SAPPANWOOD
		SDL_Color{ 68, 49, 46, 255 },		//VANISHING_RED_MOUSE
		SDL_Color{ 93, 63, 106, 255 },		//BELLFLOWER
		SDL_Color{ 63, 49, 58, 255 },		//DISAPPEARING_PURPLE
		SDL_Color{ 58, 36, 59, 255 },		//DEEP_PURPLE
		SDL_Color{ 141, 96, 140, 255 },		//HALF_COLOR
		SDL_Color{ 79, 40, 75, 255 },		//PURPLE
		SDL_Color{ 118, 53, 104, 255 },		//IRIS_COLOR
		SDL_Color{ 73, 30, 60, 255 },		//RABBIT_EAR_IRIS
		SDL_Color{ 99, 66, 75, 255 },		//GRAPE_MOUSE
		SDL_Color{ 77, 59, 60, 255 },		//WISTERIA_AND_BURNT_BAMBOO
		SDL_Color{ 143, 65, 85, 255 },		//PLUM_PURPLE
		SDL_Color{ 81, 44, 49, 255 },		//PURPLE_KITE
		SDL_Color{ 89, 41, 44, 255 }		//MULBERRY_DYE
	};
		
	colorlayouts_ = std::vector<std::vector<SDL_Color>*>{
		new std::vector<SDL_Color>{
			standardcolorvector_[VIOLET],			//BACKGROUND_COLOR
			standardcolorvector_[BLACK],			//DEMO_SCREEN_COLOR
			standardcolorvector_[BLACK],			//INPUT_SCREEN_COLOR
			standardcolorvector_[WHITE],			//TEXT_COLOR
			standardcolorvector_[BLACK],			//OUTLINED_BOX_COLOR
			standardcolorvector_[RABBIT_EAR_IRIS],	//BUTTON_BACKGROUND_COLOR
			standardcolorvector_[IRIS_COLOR],		//BUTTON_UNPRESSED_COLOR
			standardcolorvector_[BELLFLOWER],		//BUTTON_PRESSED_COLOR
			standardcolorvector_[TREE_PEONY],		//TAB_BACKGROUND_COLOR
			standardcolorvector_[PLUM_PURPLE],		//TAB_UNPRESSED_COLOR
			standardcolorvector_[VINE_GRAPE],		//TAB_PRESSED_COLOR
			standardcolorvector_[SAPPANWOOD],		//CAPTION_CONTAINER_COLOR
			standardcolorvector_[WHITE],			//CAPTION_CONTAINER_SELECTED_COLOR
			standardcolorvector_[RED_WISTERIA],		//CAPTION_CONTAINER_DRAWN_CAPTION_COLOR
			standardcolorvector_[DARK_RED]			//TEXT_INPUT_BOX
		}
	};

	currentcolorlayout_ = colorlayouts_[DEFAULT_COLOR_LAYOUT];
}

void UIElements::CloseLayouts()
{
	colorlayouts_.clear();
}

void UIElements::SetColorLayout(int colorlayout)
{
	currentcolorlayout_ = colorlayouts_[colorlayout];
}

SDL_Color UIElements::GetSDLColor(int color, int alphavalue)
{
	SDL_Color colortoreturn = standardcolorvector_[color];
	colortoreturn.a = alphavalue;

	return colortoreturn;
}

SDL_Color UIElements::GetUIElementColor(int uielement, int alphavalue)
{
	SDL_Color colortoreturn = currentcolorlayout_->at(uielement);
	colortoreturn.a = alphavalue;

	return colortoreturn;
}

SDL_Color UIElements::InvertColor(SDL_Color color) {
	SDL_Color colortoreturn = color;
	colortoreturn.r += 127;
	colortoreturn.g += 127;
	colortoreturn.b += 127;

	return colortoreturn;
}

void UIElements::ShowAsUIElement(SDL_Rect uiarea, int uielement, TextInput *text)
{
	SDLUtility::CreateSquare(uiarea, GetUIElementColor(BUTTON_BACKGROUND_COLOR, SOLID_COLOR));

	if (uielement == BUTTON_UNPRESSED)
	{
		SDLUtility::CreateBorderedRect(
			SDL_Rect{
				uiarea.x + 4,
				uiarea.y + 2,
				uiarea.w - 8,
				uiarea.h - 4 },
			GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR),
			GetUIElementColor(BUTTON_UNPRESSED_COLOR, SOLID_COLOR));
	}

	if (uielement == BUTTON_PRESSED)
	{
		SDLUtility::CreateBorderedRect(
			SDL_Rect{
			uiarea.x + 4,
			uiarea.y + 2,
			uiarea.w - 8,
			uiarea.h - 4 },
			GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR),
			GetUIElementColor(BUTTON_PRESSED_COLOR, SOLID_COLOR));
	}

	if (text != NULL)
		SDLUtility::PostText(text, (uiarea.x + 4) + 5, (uiarea.y + 2) + static_cast<int>((uiarea.h - 4 - text->GetHeight()) * .5));
}
