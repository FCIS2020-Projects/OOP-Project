#include "Game.h"
#include "Collider.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include "Goomba.h"
#include "Plant.h"

GameObject *Mushroom;
Map *map;
Player *Mario;
SDL_Renderer *Game::renderer = 0;
SDL_Event Game::e;
SDL_Rect Game::camera = { 0,0,13504,960 };
Goomba *G1, *G2 ,*G3 ,*G4;
Plant  *P1 ,*P2;


Game::Game()
{
}
void Game::init(const char title[], int x, int y, int w, int h, int flag)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen_width = w;
	screen_height = h;
	window = SDL_CreateWindow(title,x,y,w,h,flag);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 107, 140, 255, 255);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	map = new Map();
	Mario = new Player("assets/NES - Super Mario Bros - Mario.png",128,732,16,16,4);
	Mushroom = new GameObject("assets/Mushroom.png",1000,732,16,16,4);

	G1 = new Goomba("assets/Goomba.png", 2850, 732, 16, 16, 4);
	G2 = new Goomba("assets/Goomba.png", 2700, 732, 16, 16, 4);
	G3 = new Goomba("assets/Goomba.png", 3150, 732, 16, 16, 4);
	G4 = new Goomba("assets/Goomba.png", 3300, 732, 16, 16, 4);
	P1 = new Plant("assets/Plant.png", 2975, 550, 16, 22, 4);
	P2 = new Plant("assets/Plant.png", 3680, 550, 16, 22, 4);


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
	
	camera.x = Mario->position.x - screen_width / 2;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.x > camera.w-screen_width)
		camera.x = camera.w-screen_width;
	
	Mario->update();
	if (Mario->active == 0) {
		return;
	}
	G1->update(Mario);
	G2->update(Mario);
	G3->update(Mario);
	G4->update(Mario);
	P1->update(Mario);
	P2->update(Mario);


	if (Mushroom->active)
	{
		Mushroom->update();
		if (Collider::CheckCollision(Mario->dest, Mushroom->dest))
		{
			Mario->super = 1;
			Mario->src.y = 0;
			Mario->src.h = 32;
			Mario->dest.h = 32*4;
			Mario->position.y = Mario->dest.y - 16*4;
			Mix_PlayChannel(-1, powerup, 0);
			Mushroom->active = 0;
		}
	}
}
void Game::render()
{
	SDL_RenderClear(renderer);//start
	P1->render(SDL_FLIP_NONE);
	P2->render(SDL_FLIP_NONE);


	map->DrawMap();
	Mario->render(flip);
	
	if (G1->active) {
		G1->render(SDL_FLIP_NONE);
	}

	if (G2->active)
	{
		G2->render(SDL_FLIP_NONE);
	}

	if (G3->active) {
		G3->render(SDL_FLIP_NONE);
	}

	if (G4->active)
	{
		G4->render(SDL_FLIP_NONE);
	}
	
	if(Mushroom->active)
		Mushroom->render(SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);//end
}
void Game::capFPS(int start)
{
	int FPS = 60;
	int frameDelay = 1000 / FPS;
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
