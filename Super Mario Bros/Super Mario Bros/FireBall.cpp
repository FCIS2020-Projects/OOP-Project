#include "FireBall.h"



FireBall::FireBall(const char *texturefile, int x, int y, int w, int h, int scale):GameObject(texturefile, x, y, w, h, scale)
{
	speed = 7;
	velocity.x = 1;
	velocity.y = -1;
	active = 0;
}

void FireBall::update()
{
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;
	if (lastPosition - 128 >= position.y)
		velocity.y = 1;
	handleCollision();
	handleAnimation();
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
	if (dest.x <= 0 || dest.x >= 1024)
		active = 0;
}
void FireBall::handleCollision()
{
	Collider *c = Collider::CheckCollision(position, dest);
	if (c[0].m <8 && c[0].m >-1)
	{
		position.y = c[0].collider.y + c[0].collider.h;
		velocity.y = 1;
	}
	if (c[1].m <8 && c[1].m >-1)
	{
		position.y = c[1].collider.y - dest.h;
		velocity.y = -1;
		lastPosition = position.y;
	}

	if (c[2].m <8 && c[2].m >-1)
	{
		active = 0;
	}
	if (c[3].m <8 && c[3].m >-1)
	{
		active = 0;
	}
}
void FireBall::handleAnimation()
{
	src.x = 16 * ((SDL_GetTicks() / 100) % 4);
}
FireBall::~FireBall()
{
}
