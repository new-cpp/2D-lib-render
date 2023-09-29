#include "rectangle.h"
#include "traingle.h"

#include <algorithm>
Rectangle::Rectangle(SDL_Renderer* t_renderer, int left, int bottom, int width, int height, const SDL_Color& t_color)
{
	m_color = t_color;

	// store the vertex to arrays
	m_vx[0] = left;
	m_vy[0] = bottom;
	m_vx[1] = left;
	m_vy[1] = bottom + height;
	m_vx[2] = left + width;
	m_vy[2] = bottom + height;
	m_vx[3] = left + width;
	m_vy[3] = bottom ;
	
	computeBounds();

	//render the shape into a texture
	update(t_renderer);
}

Rectangle::~Rectangle(){}

SDL_FRect Rectangle::getBounds()
{
	return m_bounds;
}

void Rectangle::computeBounds()
{
	auto min_maxX = std::minmax_element(m_vx.begin(), m_vx.end());
	auto min_maxY = std::minmax_element(m_vy.begin(), m_vy.end());

	*min_maxX.first -= 1;
	*min_maxX.second += 1;
	*min_maxY.first -= 1;
	*min_maxY.second -= 1;

	m_bounds.x = *min_maxX.first;
	m_bounds.y = *min_maxY.first;
	m_bounds.w = *min_maxX.first - *min_maxX.second;
	m_bounds.h = *min_maxY.first - *min_maxY.second;
}

void Rectangle::update(SDL_Renderer* t_renderer)
{
	//initialze the texture
	initTexture(t_renderer);

	//allocate memory for pixel buffer
	Uint32* tempPixels = new Uint32[m_bounds.w * m_bounds.h];
	//clear the buffer
	std::memset(tempPixels, 0, m_bounds.w * m_bounds.h*sizeof(Uint32));

	//render the traingle into pixel buffer
	std::array<int, 3>vX1{m_vx[0], m_vx[1], m_vx[3] };
	std::array<int, 3>vY1{m_vy[0], m_vy[1], m_vy[3] };
	std::array<int, 3>vX2{m_vx[1], m_vx[2], m_vx[3] };
	std::array<int, 3>vY2{m_vy[1], m_vy[2], m_vy[3] };

	Traingle::renderTraingle(tempPixels, vX1, vY1, m_bounds, m_color);
	Traingle::renderTraingle(tempPixels, vX2, vY2, m_bounds, m_color);

	//update the texture with pixel buffer
	SDL_UpdateTexture(m_texture, nullptr, tempPixels, m_bounds.w * sizeof(Uint32));

	//delete the buffer
	delete[] tempPixels;

}

bool Rectangle::render(SDL_Renderer* t_renderer)
{

	if (t_renderer)
	{
		//to render we simply blit the texture into the renderer at the right position
		SDL_FRect srcRect;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = m_bounds.w;
		srcRect.h = m_bounds.h;

		SDL_RenderTexture(t_renderer, m_texture, &srcRect, &m_bounds);
		return true;
		return true;
	}
	else
	{
		return false;
	}

}

void Rectangle::translate(const SDL_Point& t_vect)
{

}

void Rectangle::rotate(SDL_Renderer* t_renderer,float theta)
{
	// we want to rotate about the middle of the bounding box
	float rCenterX = m_bounds.x + m_bounds.w/2.0;
	float rCenterY = m_bounds.y + m_bounds.h / 2.0;

	//loop through all vertices and applay the rotation
	float sinTheta = sin(theta);
	float cosTheta = cos(theta);

	for (int i = 0; i < 4; ++i)
	{
		float normX = m_vx[i] - rCenterX;
		float normY = m_vy[i] - rCenterY;
		float newX = normX*cosTheta - normY*sinTheta;
		float newY = normX*sinTheta + normY*cosTheta;

		m_vx[i] = round(newX + rCenterX);
		m_vy[i] = round(newY + rCenterY);
	}

	//recompute the bounding box
	computeBounds();
	//update the texture
	update(t_renderer);
}
void Rectangle::interpolate( SDL_Point p1,  SDL_Point p2, std::vector<SDL_Point>* t_edges)
{
	//if two point represent horizontal line we ignore them
	if (p1.y != p2.y)
	{
		if (p2.y < p1.y)
		{
			std::swap(p1.x, p2.x);
			std::swap(p1.y, p2.y);
		}

		int yrange = p2.y - p1.y;
		int xrange = p2.x - p1.x;

		float xstep = static_cast<float>(xrange) / static_cast<float>(yrange);

		//loop through each x and compute y accordainly
		int count = 0;
		for (int ty = p1.y; ty < p2.y; ++ty)
		{
			int tx = static_cast<int> (round(p1.x + (xstep * static_cast<float>(count))));
			t_edges->push_back({ tx,ty });
			++count;
		}
	}
}

bool Rectangle::pointSortFnc(SDL_Point a, SDL_Point b)
{
	return a.y < b.y;
}
