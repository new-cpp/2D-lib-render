#include "object.h"

bool Object::setColor(SDL_Color t_color)
{
	m_color = t_color;
	return true;
}

SDL_Color Object::getColor()
{
	return m_color;
}

void Object::initTexture(SDL_Renderer* t_renderer)
{
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;

#endif // 

	//Texture that will contain image pixels
	auto format = SDL_GetPixelFormatEnumForMasks(32, rmask, gmask, bmask, amask);
	SDL_Surface* tmp_surface = SDL_CreateSurface(m_bounds.w, m_bounds.h, format);
	auto msg = SDL_GetError();

	m_texture = SDL_CreateTextureFromSurface(t_renderer, tmp_surface);
	SDL_DestroySurface(tmp_surface);
}

Uint32 Object::convertColor(const SDL_Color& t_color)
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 pixelColor = (t_color.r << 24) + (t_color.g << 16) + (t_color.b << 8) + (255);
#else
	Uint32 pixelColor = (255 << 24) + (t_color.b << 16) + (t_color.g << 8) + (t_color.r);
#endif

	return pixelColor;
}