#pragma once
#include "Game.h"

class GameObject
{

	SDL_Texture *texture;
public:
	int speed;
	bool active;
	Vector2D position;
	Vector2D velocity;
	SDL_Rect src, dest;
	GameObject(const char *texturefile, int x, int y, int w, int h,int scale);
	void update();
	void handleCollision();
	void render(SDL_RendererFlip flip);
	~GameObject();
};

