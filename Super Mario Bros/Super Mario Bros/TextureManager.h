#pragma once
#include "Game.h"

class TextureManager
{
public:
	TextureManager();
	static SDL_Texture *LoadTexture(const char *filename);
	~TextureManager();
};

