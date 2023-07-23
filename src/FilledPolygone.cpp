#include "FilledPolygone.h"

#include <algorithm>

FilledPolygone::FilledPolygone(SDL_Renderer* t_renderer, const std::vector<SDL_Point>& t_vertexs, const SDL_Color&& t_color)
{
	m_vertexs = t_vertexs;
	m_color = t_color;

	computeBounds();
	update(t_renderer);
}

FilledPolygone::~FilledPolygone()
{

}

SDL_FRect FilledPolygone::getBounds()
{
	return m_bounds;
}

void FilledPolygone::computeBounds()
{
	auto [minX, maxX] = std::minmax_element(m_vertexs.begin(), m_vertexs.end(),
		[](const SDL_Point& p1, const SDL_Point& p2) {return p1.x < p2.x; });

	auto [minY, maxY] = std::minmax_element(m_vertexs.begin(), m_vertexs.end(),
		[](const SDL_Point& p1, const SDL_Point& p2) {return p1.y < p2.y; });

	// make the bound slightly bigger the shape 
	--minX->x, --minY->y, ++maxX->x, ++maxY->y;

	m_bounds.x = minX->x;
	m_bounds.y = minY->y;
	m_bounds.h = (maxY->y - minY->y);
	m_bounds.w = (maxX->x - minX->x);

}

//function to render the shape into texture
void FilledPolygone::update(SDL_Renderer* t_renderer)
{
	initTexture(t_renderer);

	//allocation for pixel buffer
	Uint32* tmpBuffer = new Uint32[m_bounds.w * m_bounds.h];
	std::fill(tmpBuffer, tmpBuffer + static_cast<int>(m_bounds.w * m_bounds.h), 0);

	auto pixelColor = convertColor(m_color);
	auto pixelColor2 = convertColor(SDL_Color{255,0,0,255});

	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;

	int detA, n = m_vertexs.size();
	float u, v;

	for (int x = 0; x < m_bounds.w; ++x)
	{
		for (int y = 0; y < m_bounds.h; ++y)
		{
			int count = 0;
			for (int i = 0; i < n; ++i)
			{
				//form the vertices for the search line
				x1 = x+m_bounds.x;
				y1 = y + m_bounds.y;
				x2 = m_bounds.w+m_bounds.x;
				y2 = y1;

				//extract the 2 vectices form the edges
				x3 = m_vertexs[i].x;
				y3 = m_vertexs[i].y;
				x4 = m_vertexs[(i+1)%n].x;
				y4 = m_vertexs[(i+1)%n].y;

				detA = (x1 - x2) * (y4 - y3) - (x4 - x3) * (y1 - y2);
				if (detA)// interseaction
				{
					u = static_cast<float>(((x1 - x3) * (y4 - y3) + (x3 - x4) * (y1 - y3))/static_cast<float>(detA));
					v = static_cast<float>(((x1 - x3) * (y2 - y1) + (x1 - x2) * (y1 - y3)) / static_cast<float>(detA));

					/*if u and v both between 0 and 1 == valid intersaction*/
					if (u > 0.0 && u < 1.0 && v>0.0 && v < 1.0)
					{
						/* how many edges intersect with our current search line*/
						++count;
					}
				}

			}

			//if count is odd set the pixel
			if (count % 2)
			{
				tmpBuffer[static_cast<int>(y * m_bounds.w) + x] = pixelColor;
			}
		}
	}

	SDL_UpdateTexture(m_texture, nullptr, tmpBuffer, m_bounds.w * sizeof(Uint32));
	delete[] tmpBuffer;

}

bool FilledPolygone::render(SDL_Renderer* t_renderer)
{
	if (t_renderer == nullptr) return false;
	//to renderer we simply blit texture into the renderer at the right position

	SDL_FRect src_rect;
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = m_bounds.w;
	src_rect.h = m_bounds.h;

	SDL_RenderTexture(t_renderer, m_texture, &src_rect, &m_bounds);
		return true;
}