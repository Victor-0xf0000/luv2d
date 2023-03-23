#pragma once

#include <engine/base.hpp>

#include <engine/graphics/geometry.hpp>

namespace luv
{
  struct Texture;
  struct RenderCmd
  {
    luv::Ref<luv::Texture> texture; // texturing, can be null
    luv::Geometry geometry; // vertices and colors, can't be null
  };
}
