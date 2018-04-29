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
<<<<<<< HEAD

=======
	bool Complete=0;
>>>>>>> c9828ce0e51f6f6d2c435bac0c8bd90c734f30b1
public:
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
<<<<<<< HEAD
	void Fire();
=======
>>>>>>> c9828ce0e51f6f6d2c435bac0c8bd90c734f30b1
	~Player();
};

