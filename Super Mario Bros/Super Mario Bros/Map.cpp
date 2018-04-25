#include "Map.h"
#include "TextureManager.h"
#include <fstream>

int Map::map[15][211];
_pair Map::arr_Vib[15][211];
Map::Map()
{
	tileset = TextureManager::LoadTexture("assets/terrain_ss.png");
	LoadMap("assets/Map.map");
	src.x = src.y = 0;
	position.x = position.y = 0;
	dest.x = dest.y = 0;
}

void Map::LoadMap(const char* fileName)
{
	int x, y, w, h;
	std::fstream file;
	file.open(fileName);
	file >> x >> y >> w >> h;

	src.w = w;
	src.h = h;
	dest.w = w * 4;
	dest.h = h * 4;

	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
		{
			file >> map[i][j];
		}
}
void Map::DrawMap()
{
	for(int i = 0 ; i < 15 ; i++)
		for (int j = 0; j < 211; j++)
		{

			position.x = j * 16*4;
			position.y = i * 16*4;
			dest.x = position.x-Game::camera.x;
			dest.y = position.y;
			if (arr_Vib[i][j].second==0 && arr_Vib[i][j].first>0)
			{
				arr_Vib[i][j].first += 1;
				dest.y -= 5;
			}
			else if (arr_Vib[i][j].first>0) {
				dest.y += 5;
				arr_Vib[i][j].first--;
			}
			if (arr_Vib[i][j].first >= 15)
			{
				arr_Vib[i][j].second = true;
			}
			if (map[i][j] != -1)
			{
				src.x = 16 * (map[i][j] % 10);
				src.y = 16 * (map[i][j] / 10);
				TextureManager::Draw(tileset, src, dest);
				
			}
		}
}
Map::~Map()
{
}
