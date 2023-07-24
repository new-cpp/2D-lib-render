#ifndef FILLEDPOLYGONE_H
#define FILLEDPOLYGONE_H

#include "object.h"

#include <vector>
class FilledPolygone : Object
{
public:
	FilledPolygone(SDL_Renderer* t_renderer, const std::vector<SDL_Point>& t_vertexs, const SDL_Color&& t_color);
	virtual ~FilledPolygone()override;

	virtual SDL_FRect getBounds() override;
	virtual bool render(SDL_Renderer* t_renderer) override;
	virtual void translate(const SDL_Point& t_vector) override;


private:
	void computeBounds();
	void update(SDL_Renderer* t_renderer);

	std::vector<SDL_Point> m_vertexs;

};
#endif