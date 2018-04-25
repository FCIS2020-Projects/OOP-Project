#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "Game.h"
#include "Player.h"

class Goomba : public GameObject
{
	bool right = true;
	int co = 120;
public:
	
	Goomba(const char *texturefile, int x, int y, int w, int h, int scale);
	void update(Player*);
	void handleanimation();
	void handleCollision();
	void handleMarioCollision(Player*);
	~Goomba();
};

