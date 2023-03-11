#pragma once

#include <engine/core/time.hpp>

namespace luv
{
  struct Engine;
  struct Clock
  {
    friend Engine;
  public:
    Clock();
    
    void create();
    void tick();

    luv::Time getDeltaTime() const;
    luv::Time getCurrTime() const;
  private:
    luv::Time dt; // delta time
    luv::Time lt; // last time
    luv::Time currTime; // Time elapsed since the engine started
  
  };
}
