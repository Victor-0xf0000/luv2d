#pragma once

#include <engine/core/luv_math.hpp>
#include <engine/graphics/color.hpp>

namespace luv
{
  struct VertexData
  {
    luv::vec2f vertice; // position
    luv::vec2f uv; // texture related
    luv::Color color;
  };

  struct Geometry
  {
    luv::VertexData* vertexData;
    int vertex_count;
  };
}
