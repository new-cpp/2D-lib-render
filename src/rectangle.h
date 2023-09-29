#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "object.h"
#include "common.h"
#include <vector>
#include <array>
class Rectangle :public Object
{
public:
	Rectangle(SDL_Renderer* t_renderer, int left ,int bottom, int width, int height, const SDL_Color& t_color);
	virtual ~Rectangle() override;

	virtual SDL_FRect getBounds() override;
	virtual bool render(SDL_Renderer* t_renderer) override;
	virtual void translate(const SDL_Point& vect) override;
	virtual void rotate(SDL_Renderer* t_renderer,float angle) override;

private:
	void computeBounds();
	void update(SDL_Renderer* t_renderer);
	static void interpolate( SDL_Point p1,  SDL_Point p2, std::vector<SDL_Point>* edgePoints);
	static bool pointSortFnc(SDL_Point a, SDL_Point b);

private:
	std::array<int32_t, 4> m_vx;
	std::array<int32_t, 4> m_vy;
	/*TODO: float version is more presice */
	std::array<float, 4> m_fvx;
	std::array<float, 4> m_fvy;
};
#endif
