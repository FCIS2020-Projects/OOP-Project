#include "Game.h"

int main(int argc, char* argv[])
{
	
	Game game;
	game.init("Super Mario Bros.", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 960, 0);

	while (game.isRunning())
	{
		int start = SDL_GetTicks();
		game.handleEvents();
		if (!game.Paused())
		{
			game.update();
			game.render();
		}
		game.capFPS(start);
	}

	game.clean();
	return 0;
}