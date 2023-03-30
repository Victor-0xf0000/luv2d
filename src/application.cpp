#include <engine/application.hpp>


luv::Application::Application()
{
  this->engine = luv::createRef<luv::Engine>();
  this->should_quit = false; 
}

void luv::Application::init()
{
  this->engine->start();
  this->onStart();

  while (!this->should_quit)
  {
    this->engine->tick();
    this->onTick();
  }
}

void luv::Application::quit()
{
  this->should_quit = true;
}

luv::Window* luv::Application::Window()
{
  return this->engine->window.get();
}

luv::Renderer* luv::Application::Renderer()
{
  return this->engine->renderer.get();
}

luv::EventManager* luv::Application::EventManager()
{
  return this->engine->eventManager.get();
}

luv::Clock* luv::Application::Clock()
{
  return this->engine->clock.get();
}

luv::Camera* luv::Application::Camera()
{
  return this->engine->camera.get();
}

luv::AssetsManager* luv::Application::AssetsManager()
{
  return this->engine->assetsManager.get();
}
