#include <engine/engine.hpp>

#include <engine/graphics/renderer.hpp>
#include <engine/window.hpp>
#include <engine/events/eventManager.hpp>
#include <engine/core/clock.hpp>
#include <engine/core/camera.hpp>
#include <engine/assets/assetsManager.hpp>

luv::Engine::Engine()
  : window(createRef<luv::Window>()),
  renderer(createRef<luv::Renderer>()),
  eventManager(createRef<luv::EventManager>()),
  clock(createRef<luv::Clock>()),
  camera(createRef<luv::Camera>()),
  assetsManager(createRef<luv::AssetsManager>())
{
}

luv::Engine::~Engine()
{
  printf("Destroying engine\n");
}

void luv::Engine::start()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error while initializing sdl2: %s\n", SDL_GetError());
	}
  
  this->window->create("Luv2D", 800, 600);
  this->camera->create(this->window);
  this->renderer->create(this->window, this->camera);
  this->eventManager->create();
  this->clock->create();
  this->assetsManager->create(this->renderer);
}

void luv::Engine::tick()
{
  this->clock->tick();
  this->eventManager->update_events();
}
