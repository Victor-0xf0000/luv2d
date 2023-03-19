#pragma once

#include <SDL2/SDL.h>

#include <engine/base.hpp>
#include <engine/graphics/color.hpp>

#include <engine/core/luv_math.hpp>
#include <array>

namespace luv
{
  struct Window;
  struct Camera;
  struct Texture;
  struct Renderer
  {
  private:
    luv::Ref<Window> window_ptr;
    luv::Ref<Camera> camera_ptr;
    bool vsync;

    Color background_color;
  public:
    Renderer();
    ~Renderer();

    void create(luv::Ref<luv::Window> window, luv::Ref<luv::Camera> camera);
    
    bool get_vsync() const;
    void set_vsync(bool vsync);
    
    void set_background_color(Color color);

    void begin_render();
    void render_texture(const Ref<Texture>& texture, int x, int y, int width, int height);
    void render_quad(luv::Rect rect, std::array<luv::Color, 4> vertexColors);
    void render_quad(luv::Rect rect, luv::Color color);
    void end_render();
  };
}
