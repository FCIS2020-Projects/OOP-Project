#include "Collider.h"
#include "Map.h"

Collider::Collider()
{
}

bool Collider::CheckCollision(SDL_Rect r1, SDL_Rect r2)
{
	if (r1.x > r2.x + r2.w)
		return 0;
	if (r1.y > r2.y + r2.h)
		return 0;
	if (r1.x + r1.w < r2.x)
		return 0;
	if (r1.y + r1.h < r2.y)
		return 0;
	return 1;
}

Collider* Collider::CheckCollision(Vector2D position, SDL_Rect dest)
{
	SDL_Rect top = { position.x + dest.w / 2,position.y,1,1 };
	SDL_Rect bottom = { position.x + dest.w / 2,position.y + dest.h,1,1 };
	SDL_Rect right = { position.x + dest.w,position.y + dest.h / 2,1,1 };
	SDL_Rect left = { position.x,position.y + dest.h / 2,1,1 };

	Collider c[4];
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 211; j++)
		{
			SDL_Rect collider2 = { j * 64,i * 64,64,64 };
			if (CheckCollision(top, collider2))
			{
				c[0].m = Map::map[i][j];
				c[0].collider = collider2;
			}
			if (CheckCollision(bottom, collider2))
			{
				c[1].m = Map::map[i][j];
				c[1].collider = collider2;
			}
			if (CheckCollision(right, collider2))
			{
				c[2].m = Map::map[i][j];
				c[2].collider = collider2;
			}
			if (CheckCollision(left, collider2))
			{
				c[3].m = Map::map[i][j];
				c[3].collider = collider2;
			}
		}
	return c;
}
Collider::~Collider()
{
}
