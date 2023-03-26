#include <engine/graphics/texture.hpp>
#include <engine/graphics/renderer.hpp>

#include <SDL2/SDL.h>

#include <stb_image/stb_image.h>

#include <stdio.h>

#include <algorithm>
#include <array>

luv::Texture::Texture()
	: sdl_texture_ptr(nullptr)
{

}

luv::Texture::~Texture()
{
  SDL_DestroyTexture(this->sdl_texture_ptr);
}

bool luv::Texture::loadFromFile(SDL_Renderer* sdl_renderer_ptr, 
    const char* path)
{
  // TODO: refactor this late, this stinks
  int w, h, componentsPerPixel;
  u8* pixels = stbi_load(path, &w, &h, &componentsPerPixel, 0);

  if (!pixels)
  {
    fprintf(stderr, "Error reading %s\n", path);
    return false;
  }
  SDL_Surface* surface;
  
  std::array<u32, 4> masks;
  if (testByteOrder() == LITTLE_ENDIAN)
    masks = {0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000};
  else
    masks = {0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF};

  if (componentsPerPixel == 4)
    surface = SDL_CreateRGBSurfaceFrom(pixels, w, h, 32, w*4, masks[0], masks[1], masks[2], masks[3]);
  else if (componentsPerPixel == 3)
    surface = SDL_CreateRGBSurfaceFrom(pixels, w, h, 24, w*3, masks[0], masks[1], masks[2], masks[3]);
  else
  {
    printf("Error: unsupported number of components: %i\n", componentsPerPixel);
    free(pixels);
    return false;
  }

  free(pixels);
  
  if (surface)
  {
    this->sdl_texture_ptr = SDL_CreateTextureFromSurface(
        sdl_renderer_ptr,
        surface);
  }
  else
  {
    fprintf(stderr, "Couldn't create sdl surface, error: %s\n", SDL_GetError());
    return false;
  }

  SDL_FreeSurface(surface);

  return true;
}

