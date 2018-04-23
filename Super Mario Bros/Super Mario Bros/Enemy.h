#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "Game.h"
#include "Player.h"

class Enemy : public GameObject
{
	Vector2D lastPosition;
	bool right = true;
public:
	
	Enemy(const char *texturefile, int x, int y, int w, int h, int scale);
	void update(Player*);
	void handleanimation();
	void handleCollision();
	void handleMarioCollision(Player*);
	~Enemy();
};

