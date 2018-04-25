#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "Game.h"
#include "Player.h"

class Coin : public GameObject
{
public:

	Coin(const char *texturefile, int x, int y, int w, int h, int scale);
	void update(Player*);
	void handleanimation();
	void handleCollision();
	void handleMarioCollision(Player*);
	~Coin();
};
