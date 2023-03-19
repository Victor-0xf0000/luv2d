#include <engine/engine.hpp>

#include <engine/graphics/renderer.hpp>
#include <engine/window.hpp>
#include <engine/events/eventManager.hpp>
#include <engine/core/clock.hpp>
#include <engine/core/camera.hpp>

luv::Engine::Engine()
  : window(createRef<luv::Window>()),
  renderer(createRef<luv::Renderer>()),
  eventManager(createRef<luv::EventManager>()),
  clock(createRef<luv::Clock>()),
  camera(createRef<luv::Camera>())
{
}

luv::Engine::~Engine()
{

}

void luv::Engine::start()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error while initializing sdl2: %s\n", SDL_GetError());
	}
  
  this->window->create("Luv2D", 800, 600);
  this->camera->create(this->window->get_width(), this->window->get_height());
  this->renderer->create(this->window, this->camera);
  this->eventManager->create();
  this->clock->create();
}

luv::Window* luv::Engine::getWindow()
{
  return this->window.get();
}

luv::Renderer* luv::Engine::getRenderer()
{
  return this->renderer.get();
}

luv::EventManager* luv::Engine::getEventManager()
{
  return this->eventManager.get();
}

luv::Clock* luv::Engine::getClock()
{
  return this->clock.get();
}


luv::Camera* luv::Engine::getCamera()
{
  return this->camera.get();
}
