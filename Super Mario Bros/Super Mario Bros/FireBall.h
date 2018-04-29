#pragma once
#include "GameObject.h"
#include "Collider.h"

class FireBall:public GameObject
{
	int lastPosition;
public:
	FireBall(const char *texturefile, int x, int y, int w, int h, int scale);
	void handleCollision();
	void handleAnimation();
	void update();
	~FireBall();
};

