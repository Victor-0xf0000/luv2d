#pragma once

#include <engine/events/event.hpp>

namespace luv
{
  struct LUV2D_ENGINE_API EventManager
  {
  private:
    Event event;
  public:
    EventManager();
    ~EventManager();
    
    void create();

    void update_events();

    Event getEvent();
  };
}
