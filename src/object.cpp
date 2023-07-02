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

