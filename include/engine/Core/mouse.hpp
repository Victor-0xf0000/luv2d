#pragma once

namespace luv
{
  enum MouseButton
  {
    BUTTON_NULL = -1,
    BUTTON_LEFT = 0,
    BUTTON_RIGHT = 1,
    BUTTON_MIDDLE = 2
  };
  enum MouseButtonState
  {
    MOUSE_BUTTON_NULL = 0,
    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_HOLD,
    MOUSE_BUTTON_RELEASED,
    MOUSE_BUTTON_RELEASE
  };
}
