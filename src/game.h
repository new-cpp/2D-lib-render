#ifndef GAME_H
#define GAME_H
#include "common.h"
#include "object.h"

#include <vector>
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
		return m_is_Running;
	}

	std::vector<Object*> m_objects;
	std::vector<SDL_Point> m_vec_list;//translation vector of each obj

	int m_xrendersize, m_yrendersize;

	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
	bool m_is_Running{ true };
	SDL_Color m_current_color{ 0x00,0x00,0x00,0xff }; //black
};
#endif //!GAME_H
