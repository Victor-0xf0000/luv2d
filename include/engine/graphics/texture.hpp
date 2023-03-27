#pragma once

#include <SDL2/SDL.h>

#include <engine/base.hpp>
#include <engine/platform.hpp>

namespace luv
{
	struct Renderer;
	struct LUV2D_ENGINE_API Texture
	{
		friend Renderer;
	private:
    SDL_Texture* sdl_texture_ptr;  
    
    bool loadFromFile(SDL_Renderer* sdl_renderer_ptr, const char* path);
  public:
		Texture();
		~Texture();
  };
}
