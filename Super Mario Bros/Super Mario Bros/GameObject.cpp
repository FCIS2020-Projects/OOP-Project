#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"

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
	SDL_Rect collider = { position.x,position.y + dest.h,dest.w,0 };
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 211; j++)
		{
			SDL_Rect collider2 = { j * 64,i * 64,64,64 };
			if (Game::checkCollision(collider, collider2))
			{
				if (Map::map[i][j] <8 && Map::map[i][j] >-1)
					position.y = collider2.y - dest.h;
			}
		}
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
