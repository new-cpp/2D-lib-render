#include "circle.h"

#include <vector>
void Circle::computeBounds()
{
	m_bounds.h = 2 * m_raduis;
	m_bounds.w = 2 * m_raduis;
	m_bounds.x = m_center.x - m_raduis;
	m_bounds.y = m_center.y - m_raduis;
}

void Circle::update_texture(SDL_Renderer* t_renderer)
{
	initTexture(t_renderer);
	auto pixelColor = convertColor(m_color);
	// pixel buffer
	Uint32* pixel_buff = new Uint32[m_bounds.h * m_bounds.w];
	std::memset(pixel_buff, 0, m_bounds.h * m_bounds.w * sizeof(Uint32));

	//draw circle
	auto cx = m_center.x - m_bounds.x;
	auto cy = m_center.y - m_bounds.y;

	for (size_t x = 0; x <= m_bounds.w / 2; ++x)
	{
		for (size_t y = 0; y <= m_bounds.h / 2; ++y)
		{
			int circleV = Square(x - cx) + Square(y - cy) - Square(m_raduis);
			if (circleV <= 0)
			{
				pixel_buff[(y * (int)m_bounds.w) + x] = pixelColor;
				pixel_buff[(y * (int)m_bounds.w) + ((int)m_bounds.w - 1) - x] = pixelColor;
				pixel_buff[(((((int)m_bounds.h) - 1) - y) * (int)m_bounds.w) + x] = pixelColor;
				pixel_buff[(((((int)m_bounds.h) - 1) - y) * (int)m_bounds.w) + ((int)m_bounds.w - 1) - x] = pixelColor;
			}
		}
	}
	// use a raw pixel_buff to be more compatible with sdl api
	SDL_UpdateTexture(m_texture, nullptr, pixel_buff, m_bounds.w * sizeof(Uint32));
	delete[] pixel_buff;
}

bool Circle::render(SDL_Renderer* t_renderer)
{
	//return naive_pixel_circle(t_renderer);

	if (t_renderer == nullptr) return false;

	update_texture(t_renderer);
	SDL_FRect srcRect{ 0,0, m_bounds.w,m_bounds.h };
	SDL_RenderTexture(t_renderer, m_texture, &srcRect, &m_bounds);
	return true;
}

void Circle::translate(const SDL_Point& t_vector)
{
	//apply to m_center and m_bounds
	m_center.x += t_vector.x;
	m_center.y += t_vector.y;
	m_bounds.x += t_vector.x;
	m_bounds.y += t_vector.y;
}


bool Circle::naive_pixel_circle(SDL_Renderer* t_renderer)
{
	if (t_renderer == nullptr)  return false;

	SDL_SetRenderDrawColor(t_renderer, m_color.r, m_color.g, m_color.b, m_color.a);

	for (auto x = m_bounds.x; x < m_bounds.x + m_bounds.w; ++x)
	{
		for (auto y = m_bounds.y; y < m_bounds.y + m_bounds.h; ++y)
		{
			auto a = Square(m_center.x - x);
			auto b = Square(m_center.y - y);
			auto c = Square(m_raduis);
			a, b, c;
			if (Square(m_center.x - x) + Square(m_center.y - y) <= Square(m_raduis))
			{
				SDL_RenderPoint(t_renderer, x, y);
			}
		}
	}
	return true;
}

bool Circle::buffered_circle(SDL_Renderer* t_renderer)
{

	return true;
}
