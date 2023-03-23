#pragma once

#include <engine/base.hpp>
#include <engine/graphics/renderCmd.hpp>
#include <engine/core/luv_math.hpp>

namespace luv
{
  struct Texture;
  struct Camera;
  struct Renderable
  {
  private:
    luv::Ref<luv::Texture> texture;
    vec2f pos;
    vec2f scale;
    vec2f size;
    // TODO: flip
  public:
    Renderable();
    ~Renderable();
  
    virtual RenderCmd generate_command(luv::Ref<luv::Camera> camera,
        int window_width, int window_height);

    void set_texture(luv::Ref<luv::Texture> texture);
    void set_size(vec2f size);
    void set_pos(vec2f pos);
    void set_scale(vec2f scale);
  };
};
