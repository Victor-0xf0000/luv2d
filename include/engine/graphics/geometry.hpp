#pragma once

#include <engine/core/luv_math.hpp>
#include <engine/graphics/color.hpp>
#include <engine/platform.hpp>

namespace luv
{
  struct LUV2D_ENGINE_API VertexData
  {
    luv::vec2f vertice; // position
    luv::vec2f uv; // texture related
    luv::Color color;
  };

  struct LUV2D_ENGINE_API Geometry
  {
    luv::VertexData* vertexData;
    int vertex_count;
  };
}
