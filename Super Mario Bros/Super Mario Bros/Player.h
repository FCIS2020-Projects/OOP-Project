#pragma once
#include "GameObject.h"

class Player:public GameObject
{
	Mix_Chunk *smallJump_s,*superJump_s;
	bool jumping;
	Vector2D lastPosition;
public:
	bool super = 0,walking;
	Player(const char *texturefile, int x, int y, int w, int h, int magnifier);
	void update();
	void handleAnimation();
	void jump();
	~Player();
};

