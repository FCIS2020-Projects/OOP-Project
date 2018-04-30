#include "Player.h"
#include "Collider.h"
#include <iostream>

int Player::cnt_coin = 0;
int Player::cnt_score = 0;

Player::Player(const char *texturefile, int x, int y, int w, int h, int scale) :GameObject(texturefile, x, y, w, h, scale)
{
	src.y = 32;
	speed = 5;
	walking = 0;
	jumping = 0;
	smallJump_s = Mix_LoadWAV("SFX/smb_jump-small.wav");
	superJump_s = Mix_LoadWAV("SFX/smb_jump-super.wav");
	bump = Mix_LoadWAV("SFX/smb_bump.wav");
	flagpole = Mix_LoadWAV("SFX/smb_flagpole.wav");
	levelComplete = Mix_LoadWAV("Music/06-level-complete.mp3");
	dieng= Mix_LoadWAV("Music/08-you-re-dead.mp3");
	flagpole = Mix_LoadWAV("SFX/smb_flagpole.wav");
	levelComplete = Mix_LoadWAV("Music/06-level-complete.mp3");

	lastPosition = position;
	f1 = new FireBall("Assets/FIRE_BALLS.png",-100,-100,16,16,4);//2
	f2 = new FireBall("Assets/FIRE_BALLS.png", -100, -100, 16, 16, 4);//2

	

}

void Player::update()
{
	if (active == 0) {
		if (super == 1 || fire==1) {
			super = 0;
			fire = 0;
			position.y = 0;
			src.y = 32;
			src.h = 16;

			dest.h = 16 * 4;
			active = 1;
		}
		else if(super == 0 && fire == 0)
		{
			if (numOfLives > 0) {
				position.y = 0;
				
				numOfLives--;
				active = 1;
			}
			else {
			dying ++;
			if (dead_co == 63) {
				Mix_PlayChannel(-1, dieng, 0);
				
			}

			if (dead_co > 0) {
				dest.y-=2; dead_co--; 
			}
			else dest.y+=4;
			src.x = 5 * 16;
			if (dest.y > 1000)
				SDL_Quit();
			return;
		}
		}
	}
	if (position.y >= 1000)
		active = 0;
	if (Complete)
	{
		src.x = 8 * 16;
		if (dest.y > 700)
		{
			if (super)
				dest.y = 704;
			else
				dest.y = 768;

			position.x += 5;
			walking = 1;
			jumping = 0;
			if (position.x > 13120 + 64)
			{
				walking = 0;
				if( !Mix_Playing(-1))
				SDL_Quit();
			}
			handleAnimation();

			if (!Mix_Playing(-1))
				Mix_PlayChannel(-1, levelComplete, 0);
		}
		else
		{
			dest.y += 4;

			if(!Mix_Playing(-1))

				Mix_PlayChannel(-1, flagpole, 0);
		}
		return;
	}


	position.x += velocity.x * speed;
	position.y += velocity.y * speed;
	handleAnimation();
	if (position.x >= Game::camera.w-dest.w)
		position.x = Game::camera.w-dest.w;
	if (position.x <= 0)
		position.x = 0;
	if (position.y <= lastPosition.y - jumpHeight)
		velocity.y = 2;
	if(f1->active)
		f1->update();
	if(f2->active)
		f2->update();
	handleCollision();
	
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
}
void Player::handleCollision()
{
	Collider *c = Collider::CheckCollision(position,dest,super);


	if (c[0].m <8 && c[0].m >-1)
	{
		position.y = c[0].collider.y + c[0].collider.h;
		if (c[0].m == 1 || c[0].m == 2) {
			Mix_PlayChannel(-1, bump , 0);
			
		}
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
	if (c[2].m >= 8 && c[2].m < 12)
		finish();
	if (c[3].m <8 && c[3].m >-1)
	{
		position.x = c[3].collider.x + c[3].collider.w;
	}
}
void Player::handleAnimation()
{
	if (jumping)
		src.x = 4 * 16;
	else if (walking)
		src.x = 16 * ((SDL_GetTicks() / 100) % 3);
	else
		src.x = 6 * 16;
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
void Player::finish()
{
	Mix_PauseMusic();
	Complete = 1;

}
void Player::Fire()
{
	if(!f1->active && fire==1)
	{
		if (flip == SDL_FLIP_NONE)
		{
			f1->velocity.x = 1;

		}
		else
		{
			f1->velocity.x = -1;
		}
			f1->position.x = position.x;
		f1->position.y = position.y + dest.h / 2;//4
		f1->active = 1;
	}
	else if(!f2->active && fire == 1)
	{
		if (flip == SDL_FLIP_NONE)
		{
			f2->velocity.x = 1;

		}
		else
		{
			f2->velocity.x = -1;
		}
			f2->position.x = position.x;
		f2->position.y = position.y + dest.h / 2;//4
		f2->active = 1;
	}

}


Player::~Player()
{
}
