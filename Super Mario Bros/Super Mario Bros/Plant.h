#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "Game.h"
#include "Player.h"

class Plant : public GameObject
{
	bool up = true;
	double maxup = 60;
	double originalY;
public:

	Plant(const char *texturefile, int x, int y, int w, int h, int scale);
	void update(Player*);
	void handleanimation();
	void handleMarioCollision(Player*);
	~Plant();
};