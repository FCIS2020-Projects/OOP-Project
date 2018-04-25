#pragma once
#include "GameObject.h"
#include "Map.h"
class Player : public GameObject
{
	Mix_Chunk *smallJump_s, *superJump_s, *dieng;
	bool jumping;
	Vector2D lastPosition;
	const int jumpHeight = 300;
	int dead_co = 64;
public:
	bool super = 0,walking;
	Player(const char *texturefile, int x, int y, int w, int h, int scale);
	void update();
	void handleCollision();
	void handleAnimation();
	void jump();
	void dying();
	~Player();
};

