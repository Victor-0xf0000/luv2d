#pragma once

#include <engine/platform.hpp>

namespace luv
{
  // Handles window resized and window close
  struct LUV2D_ENGINE_API ApplicationEvent
  {
    int new_width, new_height;
    
    void update_state();
    
    int get_window_width() const;
    int get_window_height() const;
  };
}
