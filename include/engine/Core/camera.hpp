#pragma once

#include <engine/core/luv_math.hpp>

namespace luv
{
  struct Camera
  {
  private:
    vec2f world_pos;
    int vw, vh; // viewport width and viewport height
    float zoom;
    int ww, wh; // window width and window height
    float max_zoom, min_zoom;
  public:
    Camera();
    ~Camera();

    void create(int window_width, int window_height);
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
