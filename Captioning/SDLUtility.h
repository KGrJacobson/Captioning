#pragma once
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "Image.h"

static SDL_Window *window;
static SDL_Renderer *renderer;
static TTF_Font *font;

class SDLUtility {
public:
	static int Init();
	static void Close();
	static SDL_Renderer *GetRenderer();
	static void ClearScreen();
	static void UpdateScreen();
	static void PostImage(Image *img, int x, int y);
	static void PostImage(SDL_Texture *tex, int x, int y);
};