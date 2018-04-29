#include "Flower.h"



Flower::Flower(const char *texturefile, int x, int y, int w, int h, int scale) :GameObject(texturefile, x, y, w, h, scale)
{
	active = 0;
	velocity.x = 1;
	speed = 1;
	src.y = 16;
	FireMario = Mix_LoadWAV("SFX/smb_powerup.wav");
}

void Flower::update(Player* Pmario)
{
	position.y += velocity.y * speed;
	handleCollision();
	handleMarioCollision(Pmario);
	handleanimation();
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
}

void Flower::handleMarioCollision(Player* Pmario) {

	SDL_Rect top = { position.x + dest.w / 2,position.y,1,1 };
	SDL_Rect bottom = { position.x + dest.w / 2,position.y + dest.h,1,1 };
	SDL_Rect right = { position.x + dest.w,position.y + dest.h / 2,1,1 };
	SDL_Rect left = { position.x,position.y + dest.h / 2,1,1 };

	SDL_Rect collider2;
	
	collider2 = { static_cast<int>(Pmario->position.x),static_cast<int>(Pmario->position.y),static_cast<int>(Pmario->dest.w),static_cast<int>(Pmario->dest.h) };

	if (active == 1)
	{

		if (Collider::CheckCollision(top, collider2) || Collider::CheckCollision(bottom, collider2) || Collider::CheckCollision(right, collider2) || Collider::CheckCollision(left, collider2))
		{
			Pmario->fire = 1;
			Pmario->super = 1;
			Pmario->src.y = 48;
			Pmario->src.h = 32;
			Pmario->dest.h = 32 * 4;
			Pmario->position.y = Pmario->dest.y - 16 * 4;
			active = 0;
		}

	}
}

void Flower::handleanimation() {

	if (active) {

		src.x = 16 * ((SDL_GetTicks() / 100) % 4);

	}
}
Flower::~Flower()
{
}
