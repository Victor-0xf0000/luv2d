#pragma once

#include <engine/platform.hpp>

#include <SDL2/SDL.h>
#include <string>

namespace luv
{
  struct LUV2D_ENGINE_API Window
  {
  private:
    SDL_Window* sdl_window_ptr;

    std::string title;
    bool resizable;
    int width;
    int height;
  public:
    Window();
    ~Window();

    void create(const char* title, int width, int height);
      
    SDL_Window* get_sdl_window() const;

    int get_width() const;
    int get_height() const;
    
    bool get_resizable() const;
    void set_resizable(bool resizable);
    void resize(int width, int height);

    std::string get_title() const;
    void change_title(const char* title);
  };
}
