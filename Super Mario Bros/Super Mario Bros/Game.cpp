#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

GameObject *Map,*Mushroom;
Player *Mario;
SDL_Renderer *Game::renderer = 0;
SDL_Event Game::e;
SDL_Rect Game::camera = { 0,0,13000,864 };
Game::Game()
{
}
void Game::init(const char title[], int x, int y, int h, int w, int flag)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(title,x,y,h,w,flag);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	Map = new GameObject("assets/NES - Super Mario Bros - World 1-1.png",0,0, 3391, 216,4);
	Mario = new Player("assets/NES - Super Mario Bros - Mario.png",128,732,16,16,4);
	Mushroom = new GameObject("assets/Mushroom.png",1000,732,16,16,4);
	powerup = Mix_LoadWAV("SFX/smb_powerup.wav");
	spause = Mix_LoadWAV("SFX/smb_pause.wav");
	music = Mix_LoadMUS("Music/01-main-theme-overworld.mp3");
	Mix_PlayMusic(music, -1);
}
void Game::handleEvents()
{
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			running = 0;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				Mario->velocity.x = 1;
				Mario->walking = 1;
				flip = SDL_FLIP_NONE;
				break;
			case SDLK_LEFT:
				Mario->velocity.x = -1;
				Mario->walking = 1;
				flip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_z:
				Mario->jump();
				break;
			case SDLK_ESCAPE:
				pause = !pause;
				if (pause)
					Mix_PauseMusic();
				else
					Mix_ResumeMusic();
				Mix_PlayChannel(-1, spause, 0);
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				Mario->velocity.x = 0;
				Mario->walking = 0;
				break;
			case SDLK_LEFT:
				Mario->velocity.x = 0;
				Mario->walking = 0;
				break;
			case SDLK_z:
				Mario->velocity.y = 2;
			}
			break;
		}
	}
}
void Game::update()
{
	camera.x = Mario->position.x - 512;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	Map->dest.x = -camera.x;   
	Mario->update();
	if (Mushroom->active)
	{
		Mushroom->update();
		if (checkCollision(Mario->dest, Mushroom->dest))
		{
			Mario->super = 1;
			Mario->src.y = 0;
			Mario->src.h = 32;
			Mario->position.y = 668;
			Mario->dest.h = 32*4;
			Mix_PlayChannel(-1, powerup, 0);
			Mushroom->active = 0;
		}
	}
}
void Game::render()
{
	SDL_RenderClear(renderer);
	Map->render(SDL_FLIP_NONE);
	Mario->render(flip);
	if(Mushroom->active)
		Mushroom->render(SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
}
void Game::capFPS(int start)
{
	int frameDelay = 1000 / 60;
	int frameTime = SDL_GetTicks() - start;
	if(frameDelay>frameTime)
		SDL_Delay(frameDelay - frameTime);
}
void Game::clean()
{
	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
bool Game::checkCollision(SDL_Rect r1, SDL_Rect r2)
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
bool Game::isRunning()
{
	return running;
}
bool Game::Paused()
{
	return pause;
}
Game::~Game()
{
}
