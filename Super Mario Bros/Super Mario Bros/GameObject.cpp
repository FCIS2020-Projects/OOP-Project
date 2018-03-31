#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *texturefile,int x, int y,int w, int h, int scale)
{
	texture = TextureManager::LoadTexture(texturefile);
	src.x = 0;
	src.y = 0;
	src.w = w;
	src.h = h;

	position.x = x;
	position.y = y;

	dest.x = x;
	dest.y = y;
	dest.w = w*scale;
	dest.h = h*scale;

	velocity.x = 0;
	velocity.y = 0;
	speed = 3;
	active = 1;
}
void GameObject::update()
{
	position.x += velocity.x * speed;
	dest.x = position.x-Game::camera.x;
	dest.y = position.y;
}
void GameObject::render(SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &src, &dest,0,0,flip);
}
GameObject::~GameObject()
{
}
