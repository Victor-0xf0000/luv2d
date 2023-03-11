#pragma once

#include <engine/base.hpp>

namespace luv
{
  struct Window;
  struct Renderer;
  struct EventManager;
  struct Clock;
  struct Engine
  {
  private:
    Ref<luv::Window> window;
    Ref<luv::Renderer> renderer;
    Ref<luv::EventManager> eventManager;
    Ref<luv::Clock> clock;
  public:
    Engine();
    ~Engine();
    
    void start();

    luv::Renderer* getRenderer();
    luv::Window* getWindow();
    luv::EventManager* getEventManager();
    luv::Clock* getClock();
  };
}
