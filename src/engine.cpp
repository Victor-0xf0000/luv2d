#include <engine/engine.hpp>

#include <engine/graphics/renderer.hpp>
#include <engine/window.hpp>
#include <engine/events/eventManager.hpp>

#include <SDL2/SDL_Image.h>

luv::Engine::Engine()
  : window(createRef<luv::Window>()),
  renderer(createRef<luv::Renderer>()),
  eventManager(createRef<luv::EventManager>())
{
}

luv::Engine::~Engine()
{

}

void luv::Engine::start()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Error while initializing sdl2: %s\n", SDL_GetError());
	}
	
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    fprintf(stderr, "could not initialize sdl2_image: %s\n", IMG_GetError());
  }
  this->window->create("Luv2D", 800, 600);
  this->renderer->create(this->window);
  this->eventManager->create();
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
