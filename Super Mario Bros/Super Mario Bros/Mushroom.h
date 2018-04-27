#pragma once
#include "Goomba.h"
class Mushroom : public Goomba {

public:
	Mix_Chunk * powerup;
	Mushroom(const char *texturefile, int x, int y, int w, int h, int scale);
	void update(Player* Pmario) ;
	void handleMarioCollision(Player*);
	void handleanimation();
	~Mushroom();
};