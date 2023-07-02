#include "circle.h"

void Circle::computeBounds()
{
	m_Bounds.h = 2 * m_raduis;
	m_Bounds.w = 2 * m_raduis;
	m_Bounds.x = m_center.x - m_raduis;
	m_Bounds.y = m_center.y - m_raduis;
}

bool Circle::render(SDL_Renderer* t_renderer)
{
	if (t_renderer == nullptr)  return false;

	SDL_SetRenderDrawColor(t_renderer, m_color.r, m_color.g, m_color.b, m_color.a);

	for (auto x = m_Bounds.x; x < m_Bounds.x + m_Bounds.w; ++x)
	{
		for (auto y = m_Bounds.y; y < m_Bounds.y + m_Bounds.h; ++y)
		{
			auto a = Square(m_center.x - x);
			auto b = Square(m_center.y - y);
			auto c = Square(m_raduis);
			a, b, c;
			if (Square(m_center.x - x) + Square(m_center.y - y) <= Square(m_raduis))
			{
				SDL_RenderDrawPoint(t_renderer, x, y);
			}
		}
	}
	return true;
}