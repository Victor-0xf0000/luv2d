#pragma once

namespace luv
{
  // Handles window resized and window close
  struct ApplicationEvent
  {
    int new_width, new_height;
    
    void update_state();
    
    int get_window_width() const;
    int get_window_height() const;
  };
}
