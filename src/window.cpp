#include <SDL2/SDL.h>

#include <engine/window.hpp>

#include <glad/glad.h>

luv::Window::Window()
  : sdl_window_ptr(nullptr)
{
  
}

luv::Window::~Window()
{
  SDL_DestroyWindow(this->sdl_window_ptr);
}

void luv::Window::create(const char* title, int width, int height)
{
  this->sdl_window_ptr = SDL_CreateWindow(title, 
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
      width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  if (!this->sdl_window_ptr)
  {
    printf("Error creating window! Error: %s\n", SDL_GetError());
  }
  
  this->sdl_context = SDL_GL_CreateContext(this->sdl_window_ptr);
  SDL_GL_MakeCurrent(this->sdl_window_ptr, this->sdl_context);

  gladLoadGLLoader(SDL_GL_GetProcAddress);
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  this->title = title;
  this->width = width;
  this->height = height;
}
  
SDL_Window* luv::Window::get_sdl_window() const
{
  return this->sdl_window_ptr;
}


int luv::Window::get_width() const
{
  return this->width;
}

int luv::Window::get_height() const
{
  return this->height;
}


bool luv::Window::get_resizable() const
{
  return this->resizable; 
}

void luv::Window::set_resizable(bool resizable)
{
  this->resizable = resizable;
  SDL_SetWindowResizable(this->sdl_window_ptr, (SDL_bool)resizable);
}

void luv::Window::resize(int width, int height)
{
  if (!this->resizable)
    return;

  this->width = width;
  this->height = height;
}

std::string luv::Window::get_title() const
{
  return this->title;
}

void luv::Window::change_title(const char* title)
{
  this->title = title;
  SDL_SetWindowTitle(this->sdl_window_ptr, title);
}
