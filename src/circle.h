#ifndef CIRCLE_H
#define CIRCLE_H

#include "common.h"
#include "object.h"

class Circle : public Object
{
public:
	Circle(SDL_Point t_center, size_t t_raduis, SDL_Color t_color)
			:m_center(t_center),m_raduis(t_raduis),m_color(t_color)
	{
		computeBounds();
	}

	~Circle()override { };

	SDL_Rect getBounds() override { return m_Bounds; }
	bool render(SDL_Renderer* t_renderer) override;

	SDL_Point getCenter() { return m_center; }
	size_t getRaduis() { return m_raduis; }

private:
	void computeBounds();

	SDL_Rect m_Bounds{};
	SDL_Point m_center{};
	size_t m_raduis{};
	SDL_Color m_color{};
};
#endif // !CIRCLE_H
