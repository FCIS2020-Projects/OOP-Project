#include "Player.h"
#include "Collider.h"

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
	if (position.x >= Game::camera.w-dest.w)
		position.x = Game::camera.w-dest.w;
	if (position.x <= 0)
		position.x = 0;
	if (position.y <= lastPosition.y - jumpHeight)
		velocity.y = 2;
	handleCollision();
	
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
}
void Player::handleCollision()
{
	Collider *c = Collider::CheckCollision(position,dest);

	if (c[0].m <8 && c[0].m >-1)
	{
		position.y = c[0].collider.y + c[0].collider.h;
		velocity.y = 2;
	}
	if (c[1].m <8 && c[1].m >-1)
	{
		jumping = 0;
		position.y = c[1].collider.y - dest.h;
	}
	else
		jumping = 1;
	if (c[2].m <8 && c[2].m >-1)
	{
		position.x = c[2].collider.x - dest.w;
	}
	if (c[3].m <8 && c[3].m >-1)
	{
		position.x = c[3].collider.x + c[3].collider.w;
	}
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
