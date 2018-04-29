#include "Plant.h"

Plant::Plant(const char *texturefile, int x, int y, int w, int h, int scale) :GameObject(texturefile, x, y, w, h, scale)
{
	originalY = y;
}

void Plant::update(Player* Pmario)
{
	if (active)
	{
		
		if (up)
		{
			position.y += -2; 
			if ((originalY - position.y) > maxup)
				up = false; 
		}
		else
		{
			position.y += 1;
			//src.h -= velocity.y * speed;
			if ((position.y-originalY ) > maxup)
				up = true;

		}
	}

	position.x += velocity.x * speed;
	handleMarioCollision(Pmario);
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
	handleanimation();
}


void Plant::handleMarioCollision(Player* Pmario) {

	SDL_Rect top = { position.x + dest.w / 2,position.y,1,1 };
	SDL_Rect bottom = { position.x + dest.w / 2,position.y + dest.h,1,1 };
	SDL_Rect right = { position.x + dest.w,position.y + dest.h / 2,1,1 };
	SDL_Rect left = { position.x,position.y + dest.h / 2,1,1 };

	SDL_Rect collider2 ;

	collider2 = { static_cast<int>(Pmario->position.x) ,static_cast<int>(Pmario->position.y),static_cast<int>(Pmario->dest.w),static_cast<int>(Pmario->dest.h) };

	if (Pmario->active == 1) {
		if (Pmario->f1->active&&Collider::CheckCollision(Pmario->f1->dest, dest))
		{
			active = 0;
			Pmario->f1->active = 0;
		}
		if (Pmario->f2->active&&Collider::CheckCollision(Pmario->f2->dest, dest))
		{
			active = 0;
			Pmario->f2->active = 0;
		}
	if (Collider::CheckCollision(top, collider2))
	{
		Pmario->active = 0;
	}
	else if (Collider::CheckCollision(bottom, collider2))
	{
	}
	else if (Collider::CheckCollision(right, collider2))
	{
		Pmario->active = 0;
	}
	else if (Collider::CheckCollision(left, collider2))
	{
		Pmario->active = 0;
	}
	}

}

void Plant::handleanimation()
{
	if (active)
		src.x = 16 * ((SDL_GetTicks() / 300) % 2);
}

Plant::~Plant()
{
}
