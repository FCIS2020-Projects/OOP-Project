#pragma once
#include "Game.h"

struct _pair
{
	int first=0;
	bool second=0;
	unsigned short type; // the type of the block 
};
class Map
{
	SDL_Rect src, dest;
	SDL_Texture *tileset;
	Vector2D position;
public:
	static int map[15][211];
	static _pair arr_Vib[15][211];
	Map();
	void LoadMap(const char* fileName);
	void DrawMap();
	~Map();
};
