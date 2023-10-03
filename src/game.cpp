#include "game.h"
#include "circle.h"
#include "FilledPolygone.h"
#include "traingle.h"

#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
void Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::string msg("can't init sdl subsystem : " + std::to_string(SDL_errorcode()));
		throw(msg);
		exit(-1);
	}
	m_window = SDL_CreateWindow("2d lib demo", 640, 480, SDL_WINDOW_RESIZABLE & SDL_WINDOW_BORDERLESS);

	if (!m_window)
	{
		std::string msg("can't create window error code : " + std::to_string(SDL_errorcode()));
		throw(msg);
		exit(-1);
	}

	m_renderer = SDL_CreateRenderer(m_window, nullptr, 0);

	if (!m_renderer)
	{
		SDL_DestroyWindow(m_window);
		std::string msg("can't create window error code : " + std::to_string(SDL_errorcode()));
		throw(msg);
		exit(-1);
	}

	SDL_GetRenderOutputSize(m_renderer, &m_xrendersize, &m_yrendersize);

	m_objects.emplace_back(new Circle({ m_xrendersize - 100,360 }, 100, { 255,255,0,255 }));
	m_objects.emplace_back(new Circle({ 480,m_yrendersize - 50 }, 50, { 0,255,0,255 }));
	m_objects.emplace_back(new Circle({ 100,100 }, 75, { 0,255,255,255 }));

	std::vector<SDL_Point> traingle { {100, 100}, { 200,100 }, { 150 ,200 }};
	m_objects.push_back(new FilledPolygone(m_renderer, traingle, SDL_Color{ 45,87,8,255 }));
	
	std::vector<SDL_Point> polygone {{ 100, 100}, { 200,100 }, { 200 ,200 }, { 150,150 }, { 100,200 }};
	m_objects.push_back(new FilledPolygone(m_renderer, polygone, SDL_Color{ 0,240,0,255 }));

	m_objects.push_back(new Traingle(m_renderer, { 100,50 }, { 200,100 }, { 150,200 }, SDL_Color{ 45,77,0,255 }));
	m_objects.push_back(new Traingle(m_renderer, { 300,50 }, { 200,400 }, { 150,350 }, SDL_Color{ 45,0,0,255 }));
	m_objects.push_back(new Traingle(m_renderer, { 600,50 }, { 500,100 }, { 150,450 }, SDL_Color{ 0,77,0,255 }));


	m_vec_list.emplace_back(SDL_Point{ 1,1 });
	m_vec_list.emplace_back(SDL_Point{ -1,1 });
	m_vec_list.emplace_back(SDL_Point{ 1,1 });
	m_vec_list.emplace_back(SDL_Point{ 1,1 });
	m_vec_list.emplace_back(SDL_Point{ -1,1 });

	m_vec_list.emplace_back(SDL_Point{ -1,1 });
	m_vec_list.emplace_back(SDL_Point{ -1,1 });
	m_vec_list.emplace_back(SDL_Point{ -1,1 });




}

void Game::update()
{
	for(size_t i = 0 ; i < m_objects.size();++i)
	{
		auto objBounds = m_objects[i]->getBounds();
		
		//check if we are the edge of the window
		if ((objBounds.x < 0) || (objBounds.x + objBounds.w) > m_xrendersize)
		{
			m_vec_list[i].x *= -1;
		}
		if ((objBounds.y < 0) || (objBounds.y + objBounds.h) > m_yrendersize)
		{
			m_vec_list[i].y *= -1;
		}

		m_objects[i]->translate(m_vec_list[i]);
	}
}

void Game::inputProcess()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_EVENT_QUIT:
			m_is_Running = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (e.key.keysym.sym == SDLK_ESCAPE)
				m_is_Running = false;
			break;
		}
	}
}

void Game::render()
{
	//background
	SDL_SetRenderDrawColor(m_renderer, m_current_color.r, m_current_color.g, m_current_color.b, m_current_color.a);
	SDL_RenderClear(m_renderer);



	auto start = std::chrono::steady_clock::now();
	for (auto& ele : m_objects)
		ele->render(m_renderer);

	auto end = std::chrono::steady_clock::now();
	auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	

#if 0
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

	 circle test
	Circle c (SDL_Point{ 320, 240 }, 50, SDL_Color{ 0xff,0x00,0x00,0xff });
	//c.render(renderer);
	std::vector<Object*> obj(100);
	for (auto& ele : obj)
	{
		Uint32 raduis{ static_cast<Uint32>(rng()) % (50) + 1 }; /* half widow width*/

		SDL_Point center{ static_cast<Uint32>(rng())%640,static_cast<Uint32>(rng())%480 };
		SDL_Color color{ static_cast<Uint32>(rng()) % 255,static_cast<Uint32>(rng()) % 255,static_cast<Uint32>(rng()) % 255,255 };
		ele = new Circle(center, raduis, color);
	}

	polygone test
	//std::vector<SDL_Point> testVertices { {100,100}, { 200,100 }, {150 ,200 }};
	std::vector<SDL_Point> testVertices { {100, 100}, { 200,100 }, { 200 ,200 }, { 150,150 }, { 100,200 }};
	//std::vector<SDL_Point> testVertices { {100, 100}, { 200,100 }, { 200 ,200 }, { 100,200 }};
	FilledPolygone poly(renderer, testVertices, SDL_Color{255,255,0,255});
	poly.render(renderer);
	/*for (auto ele : obj)
	{
		ele->render(renderer);
	}*/
#endif
	SDL_Delay(5u);
	SDL_RenderPresent(m_renderer);
}


void Game::destroy()
{
	for (auto& ele : m_objects)
		delete ele;

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = nullptr;
	m_window = nullptr;
	SDL_Quit();
}