#include "Map.h"
#include "TextureManager.h"
#include <fstream>
#include "Player.h"
#include <iostream>

int Map::map[15][211];
_pair Map::arr_Vib[15][211];
Map::Map()
{
	tileset = TextureManager::LoadTexture("assets/terrain_ss.png");
	bp = TextureManager::LoadTexture("assets/blockpart.png");
	coin = TextureManager::LoadTexture("assets/coin_block.png");
	LoadMap("assets/Map.map");
	src.x = src.y = 0;
	position.x = position.y = 0;
	dest.x = dest.y = 0;
	Coin_Music = Mix_LoadWAV("SFX/smb_coin.wav");
	
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
	int T = 19;
	while (T--) {
		int a, b, c;
		file >> b;
		file >> a;
		file >> c;
		arr_Vib[a][b].type = c;
		arr_Vib[a][b].co = (arr_Vib[a][b].type == 1) ? 3 : 1;
	}
	file.close();
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
			if (arr_Vib[i][j].second == 2) {
				map[i][j] = -1;
				arr_Vib[i][j].second = 3;
			}

			if (arr_Vib[i][j].second == 4 || (arr_Vib[i][j].rise>0 && arr_Vib[i][j].rise<=64)) {

			switch (arr_Vib[i][j].type)
				{
				case 1:
					src.x = 0;
					src.y = 0;
					Mix_PlayChannel(-1, Coin_Music, 0);
				
					arr_Vib[i][j].rise += 4;
					dest.y -= arr_Vib[i][j].rise;
					src.x = ((SDL_GetTicks()/ 100) % 4)*16;
					TextureManager::Draw(coin, src, dest);
					dest.y += arr_Vib[i][j].rise;
					if (arr_Vib[i][j].rise == 80) {
						arr_Vib[i][j].rise = 0;
						Player::cnt_coin += 1;
					}
					break;

				case 2:
					Game::Getcoordinate(position.x, position.y,1);
					arr_Vib[i][j].type = 0;
					break;

				case 3:
					Game::Getcoordinate(position.x, position.y, 2);
					arr_Vib[i][j].type = 0;
					break;
				default:
					break;
				}
				
				if (arr_Vib[i][j].rise == 4) {
					Map::arr_Vib[i][j].co--;
					Map::arr_Vib[i][j].first = 1;
					Map::arr_Vib[i][j].second = 0;
				}
			}

			if (arr_Vib[i][j].second == 3)
			{
				if (arr_Vib[i][j].fall_b >= 700)arr_Vib[i][j].second=0;
				src.x = 0;
				src.y = 0;
				dest.y += arr_Vib[i][j].fall_b;
				dest.x -= arr_Vib[i][j].fall_b/2;
				TextureManager::Draw(bp, src, dest);
				dest.x += arr_Vib[i][j].fall_b / 2;
				dest.x -= arr_Vib[i][j].fall_b / 4;
				TextureManager::Draw(bp, src, dest);
				dest.x += arr_Vib[i][j].fall_b / 4;
				dest.x += arr_Vib[i][j].fall_b / 4;
				TextureManager::Draw(bp, src, dest);
				dest.x -= arr_Vib[i][j].fall_b / 4;
				dest.x += arr_Vib[i][j].fall_b / 2;
				TextureManager::Draw(bp, src, dest);
				dest.x -= arr_Vib[i][j].fall_b / 2;
				arr_Vib[i][j].fall_b+=8;

			}
			if (arr_Vib[i][j].second == 2) {
				map[i][j] = -1;
				arr_Vib[i][j].second = 3;
			}

			if (arr_Vib[i][j].second == 0 && arr_Vib[i][j].first > 0)
			{
				arr_Vib[i][j].first += 1;
				dest.y -= 5;
			}
			else if (arr_Vib[i][j].first > 0) {
				dest.y += 5;
				arr_Vib[i][j].first--;
				if (arr_Vib[i][j].first == 0)
					arr_Vib[i][j].second = 0;
			}
			if (arr_Vib[i][j].first >= 15)
			{
				arr_Vib[i][j].second = 1;
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
