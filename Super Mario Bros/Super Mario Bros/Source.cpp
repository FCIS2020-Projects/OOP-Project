#include "Game.h"

int main(int argc, char* argv[])
{
	
	Game game;
	game.init("Super Mario Bros.", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 960, 0);
	while (game.isRunning())
	{
		game.handleEvents();
		game.render();
		SDL_Delay(100);
	}
	game.clean();
	return 0;
}