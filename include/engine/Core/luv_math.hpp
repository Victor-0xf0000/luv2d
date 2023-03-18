#pragma once

namespace luv
{
  struct vec2f
  {
    float x;
    float y;
  };

  struct Rect
  {
    vec2f pos;
    int width, height;
  };
}
