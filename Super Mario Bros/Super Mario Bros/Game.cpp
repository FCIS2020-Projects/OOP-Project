#include "Game.h"



Game::Game()
{
}
void Game::init(const char title[], int x, int y, int h, int w, int flag)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(title,x,y,h,w,flag);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* map = IMG_Load("assets\\NES - Super Mario Bros - World 1-1.png");
	SDL_Surface* mario = IMG_Load("assets\\NES - Super Mario Bros - Mario.png");
	mapTexture = SDL_CreateTextureFromSurface(renderer, map);
	marioTexture = SDL_CreateTextureFromSurface(renderer, mario);
	SDL_FreeSurface(map);
	SDL_FreeSurface(mario);
	src.x = src.y = 0;
	src.w = 256;
	src.h = 216;
	msrc.x = 1;
	msrc.y = 1;
	msrc.h = 32;
	msrc.w = 16;
	mdst.x = 128;
	mdst.y = 756;
	mdst.h = msrc.h*4;
	mdst.w = msrc.w*4;
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	sound = Mix_LoadWAV("SFX//smb_jump-super.wav");
	music = Mix_LoadMUS("Music//01-main-theme-overworld.mp3");
	Mix_PlayMusic(music, -1);
}
void Game::handleEvents()
{
	SDL_Event e;
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
				if (mdst.x > 512)
				{
					if(src.x<3135)
						src.x += 20;

				}
				else
					mdst.x+=20;

				flip = SDL_FLIP_NONE;
				update();
				break;
			case SDLK_LEFT:
				if(mdst.x>0)
					mdst.x-=20;
				flip = SDL_FLIP_HORIZONTAL;
				update();
				break;
			case SDLK_z:
				msrc.x = 86;
				if(!Mix_Playing(1))
					Mix_PlayChannel(1, sound, 0);
				break;
			}
			break;
		case SDL_KEYUP:	
			msrc.x = 1;
			break;
		}
	}
}
void Game::update()
{
	msrc.x = 17 * (((SDL_GetTicks() / 128) % 3)+1)+1;
}
void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, mapTexture, &src, 0);
	SDL_RenderCopyEx(renderer, marioTexture, &msrc, &mdst,0,0,flip);
	SDL_RenderPresent(renderer);
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
Game::~Game()
{
}
