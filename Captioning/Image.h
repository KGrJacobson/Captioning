#ifndef IMAGE
#define IMAGE

#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Image {
public:
	~Image();
	int CreateTextureFromImage(std::string filepath);
	SDL_Texture *GetTexture();
	int GetWidth();
	int GetHeight();
	void DestroyTexture();
private:
	SDL_Texture *texture_;
	int imagewidth_;
	int imageheight_;
};

#endif //IMAGE