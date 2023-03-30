#pragma once

#include <engine/platform.hpp>
#include <engine/base.hpp>
#include <engine/engine.hpp>

namespace luv
{
  struct LUV2D_ENGINE_API Application
  {
  private:
    luv::Ref<luv::Engine> engine;
    bool should_quit;
  public:
    Application();
    virtual ~Application() {}

    virtual void onStart() {}
    virtual void onTick() {}
    
    void init();
    void quit();

    luv::Window* Window();
    luv::Renderer* Renderer();
    luv::EventManager* EventManager();
    luv::Clock* Clock();
    luv::Camera* Camera();
    luv::AssetsManager* AssetsManager();
  };
}
