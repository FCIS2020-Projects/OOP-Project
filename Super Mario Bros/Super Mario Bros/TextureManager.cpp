#include "TextureManager.h"



TextureManager::TextureManager()
{
}
SDL_Texture *TextureManager::LoadTexture(const char* filename)
{
	SDL_Surface *temp = IMG_Load(filename);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, temp);
	SDL_FreeSurface(temp);
	return texture;
}

TextureManager::~TextureManager()
{
}
