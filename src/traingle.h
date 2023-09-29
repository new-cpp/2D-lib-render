#ifndef TRAINGLE_H
#define TRAINGLE_H
#include "object.h"
#include "common.h"
#include <vector>
#include <array>
class Traingle :public Object
{
public:
	Traingle(SDL_Renderer* t_renderer, const SDL_Point& v1, const SDL_Point& v2, const SDL_Point& v3, const SDL_Color& t_color);
	virtual ~Traingle() override;

	virtual SDL_FRect getBounds() override;
	virtual bool render(SDL_Renderer* t_renderer) override;
	virtual void translate(const SDL_Point& vect) override;

	//function to actual perfrom the rendering of the traingle 
	static void renderTraingle(Uint32* pixelBuffer, std::array<int, 3> vx, std::array<int, 3> vy, SDL_FRect& bounds, SDL_Color& t_color);
private:
	void computeBounds();
	void update(SDL_Renderer* t_renderer);
	static void interpolate( SDL_Point p1,  SDL_Point p2, std::vector<SDL_Point>* edgePoints);
	static bool pointSortFnc(SDL_Point a, SDL_Point b);

private:
	std::array<int32_t, 3> m_vx;
	std::array<int32_t, 3> m_vy;
};
#endif
