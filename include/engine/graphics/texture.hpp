#pragma once

#include <SDL2/SDL.h>

#include <engine/base.hpp>

#include <glad/glad.h>

namespace luv
{
	struct Renderer;
	struct Texture
	{
		friend Renderer;
	private:
	  u8* pixels;
    int gl_texture_name;
  public:
		Texture();
		~Texture();
	  
    const u8* get_pixels() const;
    int get_texture_name();

    bool loadFromFile(const char* path);
  };
}
