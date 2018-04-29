#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Collider.h"

class Flower : public GameObject
{
	Mix_Chunk *FireMario;
public:
	Flower(const char *texturefile, int x, int y, int w, int h, int scale);
	void update(Player* Pmario);
	void handleMarioCollision(Player*);
	void handleanimation();
	~Flower();
};

