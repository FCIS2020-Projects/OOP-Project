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
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
TextureManager::~TextureManager()
{
}
