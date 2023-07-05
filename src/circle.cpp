#include "circle.h"

#include <vector>
void Circle::computeBounds()
{
	m_Bounds.h = 2 * m_raduis;
	m_Bounds.w = 2 * m_raduis;
	m_Bounds.x = m_center.x - m_raduis;
	m_Bounds.y = m_center.y - m_raduis;
}

void Circle::update_texture(SDL_Renderer* t_renderer)
{
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
	Uint32 pixelColor = (m_color.r << 24) + (m_color.g << 16) + (m_color.b << 8) + (255);
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	Uint32 pixelColor = (255 << 24) + (m_color.b << 16) + (m_color.g << 8) + (m_color.r);

#endif // 

	//Texture that will contain image pixels
	auto format = SDL_GetPixelFormatEnumForMasks(32, rmask, gmask, bmask, amask);
	SDL_Surface* tmp_surface = SDL_CreateSurface(m_Bounds.w, m_Bounds.h, format);
	auto msg = SDL_GetError();

	m_texture = SDL_CreateTextureFromSurface(t_renderer, tmp_surface);
	SDL_DestroySurface(tmp_surface);

	// pixel buffer
	Uint32* pixel_buff= new Uint32[m_Bounds.h* m_Bounds.w];
	std::memset(pixel_buff, 0, m_Bounds.h * m_Bounds.w*sizeof(Uint32));

	//draw circle
	auto cx = m_center.x - m_Bounds.x;
	auto cy = m_center.y - m_Bounds.y;

	for (size_t x = 0; x <= m_Bounds.w/ 2; ++x)
	{
		for (size_t y = 0; y <= m_Bounds.h / 2; ++y)
		{
			int circleV = Square(x - cx) + Square(y - cy) - Square(m_raduis);
			if (circleV <= 0)
			{
				 pixel_buff[(y*(int)m_Bounds.w) + x] = pixelColor;
				 pixel_buff[(y*(int)m_Bounds.w) +((int)m_Bounds.w -1)- x] = pixelColor;
				 pixel_buff[(((((int)m_Bounds.h)-1)-y)*(int)m_Bounds.w) + x] = pixelColor;
				 pixel_buff[(((((int)m_Bounds.h) - 1) - y) * (int)m_Bounds.w) +((int)m_Bounds.w - 1) - x] = pixelColor;
			}
		}
	}
	// use a raw pixel_buff to be more compatible with sdl api
	SDL_UpdateTexture(m_texture, nullptr,pixel_buff, m_Bounds.w * sizeof(Uint32));
	delete[] pixel_buff;
}

bool Circle::render(SDL_Renderer* t_renderer)
{
	//return naive_pixel_circle(t_renderer);

	if (t_renderer == nullptr) return false;

	update_texture(t_renderer);
	SDL_FRect srcRect{ 0,0, m_Bounds.w,m_Bounds.h };
	SDL_RenderTexture(t_renderer, m_texture, &srcRect, &m_Bounds);
	return true;
}

bool Circle::naive_pixel_circle(SDL_Renderer* t_renderer)
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
