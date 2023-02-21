#include <engine/engine.hpp>

#include <engine/graphics/renderer.hpp>
#include <engine/window.hpp>

luv::Engine::Engine()
  : window(new Window()), renderer(new Renderer())
{

}

luv::Engine::~Engine()
{

}

void luv::Engine::start()
{
  SDL_Init(SDL_INIT_VIDEO);
  this->window->create("Luv2D", 800, 600);
  this->renderer->create(this->window);
}

luv::Window* luv::Engine::get_window()
{
  return this->window.get();
}

luv::Renderer* luv::Engine::get_renderer()
{
  return this->renderer.get();
}
