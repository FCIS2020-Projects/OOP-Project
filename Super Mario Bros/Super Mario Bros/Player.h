#pragma once
#include "GameObject.h"
#include "Map.h"
#include "FireBall.h"

class Player : public GameObject
{
	Mix_Chunk *smallJump_s, *superJump_s, *dieng ,*bump,*flagpole,*levelComplete;
	bool jumping;
	Vector2D lastPosition;
	const int jumpHeight = 300;
	int dead_co = 64;

public:
	int numOfLives = 2;
	static int cnt_coin;
	static int cnt_score;
	
	SDL_RendererFlip flip;
	FireBall *f1,*f2;
	bool super = 0, walking, fire = 0, Complete = 0;
	int dying = -1;
	Player(const char *texturefile, int x, int y, int w, int h, int scale);
	void update();
	void handleCollision();
	void handleAnimation();
	void jump();
	
	void finish();

	void Fire();
	~Player();
};

