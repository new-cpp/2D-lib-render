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

	SDL_FRect getBounds() override { return m_bounds; }
	bool render(SDL_Renderer* t_renderer) override;
	virtual void translate(const SDL_Point& t_vector) override;


	SDL_Point getCenter() { return m_center; }
	size_t getRaduis() { return m_raduis; }

	/*
	* naive drawing pixels
	*/
	bool naive_pixel_circle(SDL_Renderer* t_renderer);

	/*
	* using uint32 pixel buffer into texture
	*/
	bool buffered_circle(SDL_Renderer* t_renderer);
	


private:
	void computeBounds();
	void update_texture(SDL_Renderer* t_renderer);

	SDL_Point m_center{};
	size_t m_raduis{};
	SDL_Color m_color{};
};
#endif // !CIRCLE_H
