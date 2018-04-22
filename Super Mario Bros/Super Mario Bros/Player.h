#pragma once
#include "GameObject.h"

class Player : public GameObject
{
	Mix_Chunk *smallJump_s,*superJump_s;
	bool jumping;
	Vector2D lastPosition;
	const int jumpHeight = 300;
public:
	bool super = 0,walking;
	Player(const char *texturefile, int x, int y, int w, int h, int scale);
	void update();
	void handleCollision();
	void handleAnimation();
	void jump();
	~Player();
};

