#pragma once
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "Image.h"
#include "TextInput.h"

static SDL_Window *window;
static SDL_Renderer *renderer;

const static int SCREENW = 1500;
const static int SCREENH = 750;

class SDLUtility {
public:
	static int Init();
	static void Close();
	static SDL_Renderer *GetRenderer();
	static void GetScreenWH(int *w, int *h);
	static void ClearScreen();
	static void UpdateScreen();
	static void PostImage(Image *img, int x, int y);
	static void PostText(TextInput *text, int x, int y);
	static void PostImage(SDL_Texture *tex, int x, int y);
	static void PostImage(Image *img, int x, int y, SDL_Rect *sourcerect);
	static void CreateSquare(SDL_Rect *rect, SDL_Color *color);
};