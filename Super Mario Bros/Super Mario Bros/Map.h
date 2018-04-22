#pragma once
#include "Game.h"

class Map
{
	SDL_Rect src, dest;
	SDL_Texture *tileset;
	Vector2D position;
public:
	static int map[15][211];
	Map();
	void LoadMap(const char* fileName);
	void DrawMap();
	~Map();
};

