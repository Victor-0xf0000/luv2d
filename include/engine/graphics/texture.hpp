#pragma once

#include <SDL2/SDL.h>

#include <engine/base.hpp>

namespace luv
{
	struct Renderer;
	struct Texture
	{
		friend Renderer;
	private:
		SDL_Texture* sdl_texture_ptr;
	public:
		Texture();
		~Texture();
	};
}
