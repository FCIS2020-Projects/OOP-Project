#include "Player.h"
#include <iostream>

Player::Player(const char *texturefile, int x, int y, int w, int h, int scale) :GameObject(texturefile, x, y, w, h, scale)
{
	src.y = 32;
	speed = 5;
	walking = 0;
	jumping = 0;
	smallJump_s = Mix_LoadWAV("SFX/smb_jump-small.wav");
	superJump_s = Mix_LoadWAV("SFX/smb_jump-super.wav");
	lastPosition = position;
}
void Player::update()
{
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;
	handleAnimation();
	if (position.x >= 13564-dest.w)
		position.x = 13564-dest.w;
	if (position.x <= 0)
		position.x = 0;
	if (position.y <= lastPosition.y - 300)
		velocity.y = 2;
	if (position.y >= lastPosition.y)
	{
		jumping = 0;
		velocity.y = 0;
	}
	
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
}
void Player::handleAnimation()
{
	if (super)
	{
		if (jumping)
			src.x = 4 * 16;
		else if (walking)
			src.x = 16 * ((SDL_GetTicks() / 100) % 3);
		else
			src.x = 6 * 16;
	}
	else
	{
		if (jumping)
			src.x = 4 * 16;
		else if (walking)
			src.x = 16 * ((SDL_GetTicks() / 100) % 3);
		else
			src.x = 6 * 16;
	}
}
void Player::jump()
{
	if (!jumping)
	{
		lastPosition = position;
		velocity.y = -2;
		jumping = 1;
		if(super)
			Mix_PlayChannel(-1, superJump_s, 0);
		else
			Mix_PlayChannel(-1, smallJump_s, 0);
	}
}
Player::~Player()
{
}
