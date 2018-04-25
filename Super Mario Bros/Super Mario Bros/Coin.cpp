#include "Coin.h"
#include <iostream>

using namespace std;
Coin::Coin(const char *texturefile, int x, int y, int w, int h, int scale) :GameObject(texturefile, x, y, w, h, scale)
{
}

void Coin::update(Player* Pmario)
{
	handleCollision();
	handleMarioCollision(Pmario);
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
	handleanimation();
}

void Coin::handleCollision()
{
	Collider *c = Collider::CheckCollision(position, dest);

	if (c[0].m <8 && c[0].m >-1)
	{
		position.y = c[0].collider.y + c[0].collider.h;
		velocity.y = 2;
	}
	if (c[1].m <8 && c[1].m >-1)
	{
		position.y = c[1].collider.y - dest.h;
	}

}
void Coin::handleMarioCollision(Player* Pmario) {

	SDL_Rect top = { position.x + dest.w / 2,position.y,1,1 };
	SDL_Rect bottom = { position.x + dest.w / 2,position.y + dest.h,1,1 };
	SDL_Rect right = { position.x + dest.w,position.y + dest.h / 2,1,1 };
	SDL_Rect left = { position.x,position.y + dest.h / 2,1,1 };

	int xpos = Pmario->position.x;
	int ypos = Pmario->position.y;
	int h = Pmario->dest.h;
	int w = Pmario->dest.w;

	if (active == 1) {

		SDL_Rect collider2 = { xpos ,ypos,h,w };
		if (Collider::CheckCollision(top, collider2))
		{
			active = 0;
		}
		if (Collider::CheckCollision(bottom, collider2))
		{
		}
		if (Collider::CheckCollision(right, collider2))
		{
			active = 0;
		}
		if (Collider::CheckCollision(left, collider2))
		{
			active = 0;
		}

	}

}

void Coin::handleanimation()
{
	if (active)
		src.x = 16 * ((SDL_GetTicks() / 100) % 2);
	else
	{
		src.x = 3 * 16;
	}

}Coin::~Coin()
{
}
