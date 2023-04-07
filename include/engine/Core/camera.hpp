#pragma once

#include <engine/platform.hpp>

#include <engine/core/luv_math.hpp>
#include <engine/window.hpp>
#include <engine/base.hpp>

namespace luv
{
  struct LUV2D_ENGINE_API Camera
  {
  private:
    luv::vec2f world_pos;
    int vw, vh; // viewport width and viewport height
    float zoom;
    int ww, wh; // window width and window height
    float max_zoom, min_zoom;

    luv::Ref<luv::Window> window_ptr;
  public:
    Camera();
    ~Camera();

    void create(luv::Ref<luv::Window> window);
    void window_resized(int window_width, int window_height);
    void change_zoom(float add);
    void set_max_zoom(float max_zoom);
    void set_min_zoom(float min_zoom);
    void set_world_pos(vec2f pos);
    void move_world_pos(vec2f diff);
    Rect convert_rect_to_screen(Rect rect);
    Rect convert_rect_to_world(Rect rect);
  };
}
