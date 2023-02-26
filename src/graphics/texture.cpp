#include <engine/graphics/texture.hpp>
#include <engine/graphics/renderer.hpp>

#include <SDL2/SDL_Image.h>

luv::Texture::Texture()
	: sdl_texture_ptr(nullptr)
{

}

luv::Texture::~Texture()
{
	// If the sdl texture ptr exists
	if (this->sdl_texture_ptr)
	{
		SDL_DestroyTexture(this->sdl_texture_ptr);
	}
}
