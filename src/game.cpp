#include "game.h"
#include "circle.h"

#include <string>
#include <vector>
void Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::string msg("can't init sdl subsystem : " + std::to_string(SDL_errorcode()));
		throw(msg);
		exit(-1);
	}
	window = SDL_CreateWindow("2d lib demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE & SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		std::string msg("can't create window error code : " + std::to_string(SDL_errorcode()));
		throw(msg);
		exit(-1);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		SDL_DestroyWindow(window);
		std::string msg("can't create window error code : " + std::to_string(SDL_errorcode()));
		throw(msg);
		exit(-1);
	}

	SDL_SetRenderDrawColor(renderer, current_color.r, current_color.g, current_color.b, current_color.a);
	SDL_RenderClear(renderer);

}

void Game::update()
{
	SDL_SetRenderDrawColor(renderer, current_color.r, current_color.g, current_color.b, current_color.a);
}

void Game::inputProcess()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			is_Running = false;
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_ESCAPE)
				is_Running = false;
			break;
		}
	}
}

void Game::render()
{
	Circle c (SDL_Point{ 320, 240 }, 50, SDL_Color{ 0xff,0x00,0x00,0xff });
	//c.render(renderer);
	std::vector<Object*> obj;
	obj.emplace_back(&c);
	for (auto ele : obj)
	{
		ele->render(renderer);
	}
	SDL_RenderPresent(renderer);
}


void Game::destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;
	SDL_Quit();
}