#pragma once
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

class Image {
public:
	Image();
	~Image();
	int CreateTextureFromImage(std::string filepath);
	SDL_Texture *GetTexture();
	int GetWidth();
	int GetHeight();
	void DestroyTexture();
private:
	SDL_Texture *texture;
	int imagewidth;
	int imageheight;
};