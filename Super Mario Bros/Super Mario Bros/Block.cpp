#include "Block.h"

Block::Block(const char *texturefile, int x, int y, int w, int h, int scale,int ContainW) :GameObject(texturefile, x, y, w, h, scale) {

	if (ContainW == 1) 
	{
		RegularBlock = true;
	}
	else if (ContainW == 2){
		ContainsCoin = true;
	}
	else if (ContainW == 3){
		ContainsMashrom = true;
	}
	else if (ContainW == 4) {
		ContainsFlower = true;

	}

}

void Block::update(Player* Pmario)
{
	handleMarioCollision(Pmario);
	dest.x = position.x - Game::camera.x;
	dest.y = position.y;
	//handleanimation();
}


void Block::handleMarioCollision(Player* Pmario) {

	SDL_Rect top = { position.x + dest.w / 2,position.y,1,1 };
	SDL_Rect bottom = { position.x + dest.w / 2,position.y + dest.h,1,1 };
	SDL_Rect right = { position.x + dest.w,position.y + dest.h / 2,1,1 };
	SDL_Rect left = { position.x,position.y + dest.h / 2,1,1 };

	int xpos = Pmario->position.x;
	int ypos = Pmario->position.y;
	int h = Pmario->dest.h;
	int w = Pmario->dest.w;

	/*if (active == 1) {
		
		if (Vib.second && Vib.first>0)
		{
			Vib.first += 1;
			position.y -= 3;
		}
		else if(Vib.first>0) {
			position.y += 3;
			Vib.first--;
		}
		if (Vib.first >= 10)
		{
			Vib.second = false;
		}

		
		SDL_Rect collider2 = { xpos ,ypos,h,w };
		if (Collider::CheckCollision(bottom, collider2))
		{
			Vib.first = 1;
			Pmario->position.y = 
		}*/

	

}

//void Block::handleanimation()
//{
//	if (active)
//		src.x = 16 * ((SDL_GetTicks() / 100) % 2);
//	else
//	{
//		src.x = 3 * 16;
//	}
//}
Block::~Block()
{
}
