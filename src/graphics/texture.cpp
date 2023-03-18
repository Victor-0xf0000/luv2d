#include <engine/graphics/texture.hpp>
#include <engine/graphics/renderer.hpp>

#include <SDL2/SDL_Image.h>

#include <stb_image/stb_image.h>

#include <stdio.h>

#include <glad/glad.h>

luv::Texture::Texture()
	: pixels(nullptr)
{

}

luv::Texture::~Texture()
{
  free(this->pixels);
}

bool luv::Texture::loadFromFile(const char* path)
{
  int w, h, componentsPerPixel;
  this->pixels = stbi_load(path, &w, &h, &componentsPerPixel, 4);

  if (!this->pixels)
  {
    fprintf(stderr, "Error reading %s\n", path);
    return false;
  }
  glEnable(GL_DEPTH_TEST);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, (GLuint*)&this->gl_texture_name);
  glBindTexture(GL_TEXTURE_2D, this->gl_texture_name);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, 
      GL_RGBA, GL_UNSIGNED_BYTE, this->pixels);

  return true;
}


const u8* luv::Texture::get_pixels() const
{
  return this->pixels;
}

int luv::Texture::get_texture_name() const
{
  return this->gl_texture_name;
}
