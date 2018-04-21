#include "Player.h"
#include <iostream>
#include "Map.h"

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
	SDL_Rect colliderbottom = { position.x+16,position.y+dest.h,dest.w-32,1 };
	SDL_Rect collidertop = { position.x+16,position.y,dest.w-32,1 };
	SDL_Rect colliderleft = { position.x,position.y+16,1,dest.h-32 };
	SDL_Rect colliderright = { position.x+dest.w,position.y+16,1,dest.h-32 };
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 211; j++)
		{
			SDL_Rect collider2 = { j * 64,i * 64,64,64 };
			if (Game::checkCollision(colliderbottom, collider2))
			{
				if (Map::map[i][j] <8 && Map::map[i][j] >-1)
				{
					jumping = 0;
					position.y = collider2.y - dest.h;
					break;
				}
				else
					jumping = 1;
			}
			if (Game::checkCollision(colliderright, collider2))
			{
				if (Map::map[i][j] <8 && Map::map[i][j] >-1)
				{
					position.x = collider2.x - dest.w;
					break;
				}
			}
			if (Game::checkCollision(colliderleft, collider2))
			{
				if (Map::map[i][j] <8 && Map::map[i][j] >-1)
				{
					position.x = collider2.x + collider2.w;
					break;
				}
			}
			if (Game::checkCollision(collidertop, collider2))
			{
				if (Map::map[i][j] <8 && Map::map[i][j] >-1)
				{
					position.y = collider2.y + collider2.h;
					velocity.y = 2;
					break;
				}
			}
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
