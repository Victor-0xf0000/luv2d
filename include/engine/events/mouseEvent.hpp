#pragma once

#include <engine/Core/mouse.hpp>
#include <engine/platform.hpp>

#include <array>

namespace luv
{
  struct LUV2D_ENGINE_API MouseEvent
  {
    std::array<bool, 3> mouseButtons;
    std::array<bool, 3> prevMouseButtons;
    
    int mouse_x;
    int mouse_y;
    
    void create();
    
    void update_state();

    MouseButtonState get_button(MouseButton button);
  };
}
