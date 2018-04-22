#include "GameObject.h"
#include "TextureManager.h"
#include "Collider.h"

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
	velocity.y = 2;
	speed = 3;
	active = 1;
}
void GameObject::update()
{
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;
	handleCollision();
	dest.x = position.x-Game::camera.x;
	dest.y = position.y;
}
void GameObject::handleCollision()
{
	Collider *col = Collider::CheckCollision(position, dest);
	if (col[1].m<8 && col[1].m>-1)
		position.y = col[1].collider.y - dest.h;
}
void GameObject::render(SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &src, &dest,0,0,flip);
}
GameObject::~GameObject()
{
}
