#ifndef UI_Elements
#define UI_Elements

#include <string>
#include <vector>

#include "SDL.h"

#include "TextInput.h"
#include "SDLUtility.h"

static std::vector<SDL_Color> standardcolorvector_;
static std::vector<std::vector<SDL_Color>*> colorlayouts_;
static std::vector<SDL_Color> *currentcolorlayout_;

class UIElements 
{
public:
	static const int STANDARD_UI_FONT_SIZE = 10;

	//From the Violet Series of traditional Japanese colors
	enum Standard_Colors
	{
		BLACK,						//23,20,18
		WHITE,						//235,246,247
		WISTERIA_PURPLE,			//135,95,154
		TATARIAN_ASTER,				//151,110,154
		BLUE_VIOLET,				//43,32,40
		THIN_COLOR,					//168,124,160
		VIOLET,						//91,50,86
		DARK_RED,					//35,25,30
		RED_WISTERIA,				//187,119,150
		DOVE_FEATHER_GREY,			//117,93,91
		VINE_GRAPE,					//109,43,80
		TREE_PEONY,					//164,52,93
		FAKE_PURPLE,				//67,36,42
		SAPPANWOOD,					//126,38,57
		VANISHING_RED_MOUSE,		//68,49,46
		BELLFLOWER,					//93,63,106
		DISAPPEARING_PURPLE,		//63,49,58
		DEEP_PURPLE,				//58,36,59
		HALF_COLOR,					//141,96,140
		PURPLE,						//79,40,75
		IRIS_COLOR,					//118,53,104
		RABBIT_EAR_IRIS,			//73,30,60
		GRAPE_MOUSE,				//99,66,75
		WISTERIA_AND_BURNT_BAMBOO,	//77,59,60
		PLUM_PURPLE,				//143,65,85
		PURPLE_KITE,				//81,44,49
		MULBERRY_DYE				//89,41,44
	};

	enum Standard_Alpha_Values {
		TRANSPARENT_COLOR = 50,
		SEMITRANSPARENT_COLOR = 150,
		SOLID_COLOR = 255
	};

	//UI elements that contain multiple colors. This enum is utilized in the "uielement" argument of
	//the ShowAsUIElement function.
	enum Standard_UI_Elements {
		BUTTON_UNPRESSED,
		BUTTON_PRESSED,
		TAB_UNPRESSED,
		TAB_PRESSED
	};

	enum Standard_UI_Element_Colors {
		BACKGROUND_COLOR,
		DEMO_SCREEN_COLOR,
		INPUT_SCREEN_COLOR,
		TEXT_COLOR,
		OUTLINED_BOX_COLOR,
		BUTTON_BACKGROUND_COLOR,
		BUTTON_UNPRESSED_COLOR,
		BUTTON_PRESSED_COLOR,
		TAB_BACKGROUND_COLOR,
		TAB_UNPRESSED_COLOR,
		TAB_PRESSED_COLOR,
		CAPTION_CONTAINER_COLOR,
		CAPTION_CONTAINER_SELECTED_COLOR,
		CAPTION_CONTAINER_DRAWN_CAPTION_COLOR,
		TEXT_INPUT_BOX
	};

	enum UI_Color_Layouts {
		DEFAULT_COLOR_LAYOUT
	};

	static void Init();
	static void CloseLayouts();
	static void SetColorLayout(int colorlayout);
	static SDL_Color GetSDLColor(int color, int alphavalue);
	static SDL_Color GetUIElementColor(int uielement, int alphavalue);
	static SDL_Color InvertColor(SDL_Color color);
	static void ShowAsUIElement(SDL_Rect uiarea, int uielement, TextInput *text);
};

#endif //UI_Elements