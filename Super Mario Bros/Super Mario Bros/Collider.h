#pragma once
#include "Game.h"

class Collider
{
	
public:
	SDL_Rect collider;
	int m;
	Collider();
	static bool CheckCollision(SDL_Rect r1,SDL_Rect r2);
	static Collider* CheckCollision(Vector2D position,SDL_Rect dest,bool super=0);
	~Collider();
};

