#pragma once

#include <engine/platform.hpp>

namespace luv
{
  struct LUV2D_ENGINE_API vec2f
  {
    float x;
    float y;
  };

  struct LUV2D_ENGINE_API Rect
  {
    vec2f pos;
    int width, height;
  };
}
