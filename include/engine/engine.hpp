#pragma once

#include <memory>

namespace luv
{
  struct Window;
  struct Renderer;
  struct Engine
  {
  private:
    std::shared_ptr<luv::Window> window;
    std::shared_ptr<luv::Renderer> renderer;
  public:
    Engine();
    ~Engine();
    
    void start();

    luv::Renderer* get_renderer();
    luv::Window* get_window();
  };
}
