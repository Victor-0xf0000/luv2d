#pragma once

#include <engine/base.hpp>
#include <engine/platform.hpp>

#include <engine/core/luv_math.hpp>
#include <engine/graphics/geometry.hpp>

namespace luv
{
  struct Texture;
  struct LUV2D_ENGINE_API RenderCmd
  {
    luv::Ref<luv::Texture> texture; // texturing, can be null
    luv::vec2f pos;
    luv::vec2f size;
    luv::vec2f scale;
    
    // util when using opengl
    // vertices and colors, can't be null
    // luv::Geometry geometry; 
  };
}
