#pragma once

#include <SDL2/SDL.h>

#include <engine/base.hpp>
#include <engine/graphics/color.hpp>

namespace luv
{
  struct Window;
  struct Texture;
  struct Renderer
  {
  private:
    SDL_Renderer* sdl_renderer_ptr;
    
    bool vsync;

    Color background_color;
  public:
    Renderer();
    ~Renderer();

    void create(Ref<luv::Window> window);
    
    bool get_vsync() const;
    void set_vsync(bool vsync);
    
    void set_background_color(Color color);

    Ref<Texture> loadTexture(const char* path);

    void begin_render();
    void render_texture(Ref<Texture> texture, int x, int y, int width, int height);
    void end_render();
  };
}
