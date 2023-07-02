#include "game.h"

int main(int argc, char argv[])
{
	Game game;

	game.init();

	while (game.stillRunning())
	{
		game.inputProcess();
		game.update();
		game.render();
	}

	game.destroy();
	return 0;
}