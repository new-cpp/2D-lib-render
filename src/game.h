#ifndef GAME_H
#define GAME_H
#include "common.h"

struct Game
{
	Game() = default;
	~Game() = default;

	void init();
	void update();
	void inputProcess();
	void render();
	void destroy();

	bool stillRunning()
	{
		return is_Running;
	}

	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
	bool is_Running{ true };
	SDL_Color current_color{ 0x00,0x00,0x00,0xff }; //black
};
#endif //!GAME_H
