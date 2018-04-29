#include "Mushroom.h"


Mushroom::Mushroom(const char *texturefile, int x, int y, int w, int h, int scale) :GameObject(texturefile, x, y, w, h, scale)
{
	active = 0;
	velocity.x = 1;
	speed = 4;
	powerup = Mix_LoadWAV("SFX/smb_powerup.wav");
}

void Mushroom::update(Player* Pmario)
{
	position.x += velocity.x * speed;

	position.y += velocity.y * speed;
	handleCollision();
	handleMarioCollision(Pmario);
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
	handleanimation();
}

void Mushroom::handleMarioCollision(Player* Pmario) {

	SDL_Rect top = { position.x + dest.w / 2,position.y,1,1 };
	SDL_Rect bottom = { position.x + dest.w / 2,position.y + dest.h,1,1 };
	SDL_Rect right = { position.x + dest.w,position.y + dest.h / 2,1,1 };
	SDL_Rect left = { position.x,position.y + dest.h / 2,1,1 };

	SDL_Rect collider2;

	collider2 = { static_cast<int>(Pmario->position.x),static_cast<int>(Pmario->position.y),static_cast<int>(Pmario->dest.w),static_cast<int>(Pmario->dest.h) };

	if (active == 1)
	{

		if (Collider::CheckCollision(top, collider2) || Collider::CheckCollision(bottom, collider2) ||Collider::CheckCollision(right, collider2) || Collider::CheckCollision(left, collider2) )
		{
			Pmario->super = 1;
			Pmario->src.y = 0;
			Pmario->src.h = 32;
			Pmario->dest.h = 32 * 4;
			Pmario->position.y = Pmario->dest.y - 16 * 4;
			Mix_PlayChannel(-1, powerup, 0);
			this->active = 0;
		}

	}
}

void Mushroom::handleanimation()
{
}

Mushroom::~Mushroom()
{
}
