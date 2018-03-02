#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class Game
{
	bool running = 1;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* mapTexture, *marioTexture;
	SDL_Rect src, dst;
	SDL_Rect msrc, mdst;
	SDL_RendererFlip flip;
	Mix_Chunk *sound;
	Mix_Music *music;
public:
	Game();
	void init(const char title[],int x,int y, int h, int w, int flag);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool isRunning();
	~Game();
};

