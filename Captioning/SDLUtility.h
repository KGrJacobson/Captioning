#ifndef SDLUTILITY
#define SDLUTILITY

#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Image.h"
#include "TextInput.h"

static SDL_Window *window;
static SDL_Renderer *renderer;
static std::vector<SDL_Color> standardcolorvector;

const static int SCREENW = 1500;
const static int SCREENH = 750;

enum standardcolors
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

enum standardalphavalue {
	TRANSPARENT_COLOR = 50,
	SEMITRANSPARENT_COLOR = 150,
	SOLID_COLOR = 255
};

class SDLUtility {
public:
	static int Init();
	static void CreateColorArray();
	static void Close();
	static SDL_Renderer *GetRenderer();
	static int GetScreenWidth();
	static int GetScreenHeight();
	static SDL_Color GetSDLColor(int color, int alphavalue);
	static void ClearScreen();
	static void UpdateScreen();
	static void PostImage(Image *img, int x, int y);
	static void PostText(TextInput *text, int x, int y);
	static void PostImage(SDL_Texture *texture, int x, int y);
	static void PostImage(Image *img, int x, int y, SDL_Rect sourcerect);
	static void CreateSquare(SDL_Rect rect, SDL_Color color);
	static bool IsMouseActive(SDL_Rect mousecheckarea);
};

#endif //SDLUTILITY