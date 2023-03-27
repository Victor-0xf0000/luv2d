#pragma once

#include <engine/core/time.hpp>
#include <engine/platform.hpp>

namespace luv
{
  struct Engine;
  struct LUV2D_ENGINE_API Clock
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
