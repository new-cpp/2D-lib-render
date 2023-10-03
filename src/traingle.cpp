#include "traingle.h"

#include <algorithm>
Traingle::Traingle(SDL_Renderer* t_renderer,const SDL_Point& v1, const SDL_Point& v2, const SDL_Point& v3, const SDL_Color& t_color)
{
	m_color = t_color;

	// store the vertex to arrays
	m_vx[0] = v1.x;
	m_vx[1] = v2.x;
	m_vx[2] = v3.x;
	m_vy[0] = v1.y;
	m_vy[1] = v2.y;
	m_vy[2] = v3.y;

	computeBounds();

	//render the shape into a texture
	update(t_renderer);
}

Traingle::~Traingle(){}

SDL_FRect Traingle::getBounds()
{
	return m_bounds;
}

void Traingle::computeBounds()
{
	auto min_maxX = std::minmax_element(m_vx.begin(), m_vx.end());
	auto min_maxY = std::minmax_element(m_vy.begin(), m_vy.end());

	*min_maxX.first -= 1;
	*min_maxX.second += 1;
	*min_maxY.first -= 1;
	*min_maxY.second -= 1;

	m_bounds.x = *min_maxX.first;
	m_bounds.y = *min_maxY.first;
	m_bounds.w = *min_maxX.second - *min_maxX.first;
	m_bounds.h = *min_maxY.second - *min_maxY.first;
}

void Traingle::update(SDL_Renderer* t_renderer)
{
	//initialze the texture
	initTexture(t_renderer);

	//allocate memory for pixel buffer
	Uint32* tempPixels = new Uint32[m_bounds.w * m_bounds.h];
	//clear the buffer
	std::memset(tempPixels, 0, m_bounds.w * m_bounds.h*sizeof(Uint32));

	//render the traingle
	renderTraingle(tempPixels, m_vx, m_vy, m_bounds, m_color);

	//update the texture with pixel buffer
	SDL_UpdateTexture(m_texture, nullptr, tempPixels, m_bounds.w * sizeof(Uint32));

	//delete the buffer
	delete[] tempPixels;

}

bool Traingle::render(SDL_Renderer* t_renderer)
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

void Traingle::translate(const SDL_Point& t_vect)
{
	//apply to all vertexs and m_bound
	for (auto& ele : m_vx)
	{
		ele += t_vect.x;
	}

	for (auto& ele : m_vy)
	{
		ele += t_vect.y;
	}

	m_bounds.x += t_vect.x;
	m_bounds.y += t_vect.y;
}

void Traingle::interpolate( SDL_Point p1,  SDL_Point p2, std::vector<SDL_Point>* t_edges)
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

bool Traingle::pointSortFnc(SDL_Point a, SDL_Point b)
{
	return a.y < b.y;
}

void Traingle::renderTraingle(Uint32* pixelBuffer, std::array<int, 3> vx, std::array<int, 3> vy, SDL_FRect& bounds, SDL_Color& t_color)
{
	//normalize the input argument
	std::array<int, 3> normX;
	std::array<int, 3> normY;
	for (int i = 0; i < 3; ++i)
	{
		normX[i] = vx[i] - bounds.x;
		normY[i] = vy[i] - bounds.y;
	}

	//interpolate all the point between the vertices
	std::vector<SDL_Point> edgePoints;
	interpolate({ normX[0],normY[0] }, { normX[1],normY[1] }, &edgePoints);
	interpolate({ normX[1],normY[1] }, { normX[2],normY[2] }, &edgePoints);
	interpolate({ normX[0],normY[0] }, { normX[2],normY[2] }, &edgePoints);

	//sort xpoint and ypoint by magnitude of ypoints
	std::sort(edgePoints.begin(), edgePoints.end(), pointSortFnc);

	/* each pair of point in edgePoints should now have the same value y
	,draw a horzintal line for each value y, between the two correspandte x values*/

	Uint32 pixelColor = convertColor(t_color);
	for (int i = 0; i +1< edgePoints.size() - 1; i += 2)
	{
		// extract the cooredinate pair
		int x1 = edgePoints[i].x;
		int x2 = edgePoints[i + 1].x;
		int y1 = edgePoints[i].y;

		//swap x1 and x2 to draw from min to max
		if (x1 > x2)
			std::swap(x1, x2);

		//draw from x1 to x2
		for (int x = x1; x < x2; ++x)
		{
			pixelBuffer[y1 * static_cast<int>(bounds.w) + x] = pixelColor;
		}
	}
}
