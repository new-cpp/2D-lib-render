#ifndef OBJECT_H
#define OBJECT_H
#include "common.h"

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	bool setColor(SDL_Color t_color);
	SDL_Color getColor();
	virtual SDL_FRect getBounds() { return SDL_FRect(); };
	virtual bool render(SDL_Renderer* t_renderer) { return true; };

	void initTexture(SDL_Renderer* t_renderer);
	Uint32 convertColor(const SDL_Color& t_color);

public:
	SDL_Color m_color{ 0x00,0x00,0x00,0xff };
	int refCount{ 0 };
	SDL_FRect m_bounds;
	SDL_Texture* m_texture;
};
#endif //!OBJECT_H
