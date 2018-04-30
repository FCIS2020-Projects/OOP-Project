#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Vector2D.h"

class Game
{
	int screen_width;
	int screen_height;
	bool running = 1,pause=0;
	SDL_Window* window;
	
	Mix_Music *music;
public:
	
	Mix_Chunk *spause;
	static SDL_Rect camera;
	static SDL_Renderer* renderer;
	static SDL_Event e;
	Game();
	void init(const char title[],int x,int y, int h, int w, int flag);
	int showmenu(SDL_Surface* screen, TTF_Font* font);
	
	void handleEvents();
	void update();
	void render();
	void capFPS(int start);
	void clean();
	bool isRunning();
	bool Paused();
	static void Getcoordinate(int x, int y ,int type);
	~Game();

};