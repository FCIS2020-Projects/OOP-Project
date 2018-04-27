#pragma once
#include "Game.h"

struct _pair
{
	int first=0;
	int second=0;// 0 no move 1 move 2 break
	int type; // the type of the block 0->empty 1->coin 2->mushroom 3->flower
	int co = 0;
	int fall_b = 0;
	int rise = 0;
	
};
class Map
{

	SDL_Rect src, dest;
	SDL_Texture *tileset ,*bp ,*coin ,*flower ,*mushroom;
	Vector2D position;
public:
	static int map[15][211];
	static _pair arr_Vib[15][211];
	Map();
	void LoadMap(const char* fileName);

	void DrawMap();
	~Map();
};
