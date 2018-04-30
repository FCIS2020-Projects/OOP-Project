#include "Goomba.h"


Goomba::Goomba(const char *texturefile, int x, int y, int w, int h, int scale) :GameObject(texturefile, x, y, w, h, scale)
{
	velocity.x = 1; 
	speed = 1;
}

void Goomba::update(Player* Pmario)
{
	if (co < 120 && co != 0) {
		co--;
	}
	else
	{
	position.x += velocity.x * speed;
	}
		
	if (co == 0)
		active = 0;
	position.y += velocity.y * speed;
	handleCollision();
	handleMarioCollision(Pmario);
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
	handleanimation();
}

void Goomba::handleCollision()
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
	
	if (c[2].m <8 && c[2].m >-1)
	{
		velocity.x *=-1 ;
	}
	if (c[3].m <8 && c[3].m >-1)
	{
		velocity.x *= -1;
	}

	
}
void Goomba::handleMarioCollision(Player* Pmario) {

	SDL_Rect top = { position.x + dest.w / 2,position.y,1,1 };
	SDL_Rect bottom = { position.x + dest.w / 2,position.y + dest.h,1,1 };
	SDL_Rect right = { position.x + dest.w,position.y + dest.h / 2,1,1 };
	SDL_Rect left = { position.x,position.y + dest.h / 2,1,1 };

	SDL_Rect collider2 ;
	
	collider2 = { static_cast<int>(Pmario->position.x),static_cast<int>(Pmario->position.y),static_cast<int>(Pmario->dest.w),static_cast<int>(Pmario->dest.h) };
	
	if (active == 1 && co == 120)
	{
		if (Pmario->f1->active&&Collider::CheckCollision(Pmario->f1->dest, dest))
		{
			co--;
			Pmario->f1->active = 0;
		}
		if (Pmario->f2->active&&Collider::CheckCollision(Pmario->f2->dest, dest))
		{
			co--;
			Pmario->f2->active = 0;
		}
		if (Collider::CheckCollision(top, collider2))
		{
			Player::cnt_score += 75;
			if (co == 0) {
				active = 0;
				
			}
			else
				co--;

		}
		else if ( Collider::CheckCollision(right, collider2) || Collider::CheckCollision(left, collider2))
		{
			Pmario->active = 0;
		}
		
	}
}

void Goomba::handleanimation()
{
	if (active){

		src.x = 16 * ((SDL_GetTicks() / 100) % 2);

	}
	if(co <120 && active != 0)
	{
		src.x = 16 * 2;
	}
		
}

Goomba::~Goomba()
{
}
