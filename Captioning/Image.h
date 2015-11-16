#pragma once
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

class Image {
public:
	~Image();
	int CreateTextureFromImage(std::string filepath);
	void CreateTextureFromText(std::string text);
	SDL_Texture *GetTexture();
	int GetWidth();
	int GetHeight();
private:
	SDL_Texture *texture;
	int imagewidth;
	int imageheight;
};