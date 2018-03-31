#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

class Game
{
	bool running = 1,pause=0;
	SDL_Window* window;
	SDL_RendererFlip flip;
	Mix_Chunk *powerup,*spause;
	Mix_Music *music;
public:
	static SDL_Rect camera;
	static SDL_Renderer* renderer;
	static SDL_Event e;
	Game();
	void init(const char title[],int x,int y, int h, int w, int flag);
	void handleEvents();
	void update();
	void render();
	void capFPS(int start);
	void clean();
	bool checkCollision(SDL_Rect r1, SDL_Rect r2);
	bool isRunning();
	bool Paused();
	~Game();
};

