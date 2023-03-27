#pragma once

#include <SDL2/SDL.h>

#include <engine/base.hpp>
#include <engine/graphics/color.hpp>
#include <engine/graphics/renderCmd.hpp>

#include <engine/core/luv_math.hpp>
#include <array>

#include <vector>

namespace luv
{
  struct Window;
  struct Camera;
  struct Texture;
  struct Renderable;
  struct LUV2D_ENGINE_API Renderer
  {
  private:
    luv::Ref<Window> window_ptr;
    luv::Ref<Camera> camera_ptr;

    SDL_Renderer* sdl_renderer_ptr;

    bool vsync;

    Color background_color;
    
    std::vector<luv::RenderCmd> render_commands;
    int cmd_count;
    
    void pop_command();
    void push_command(luv::RenderCmd command);
    void run_queue();
  public:
    Renderer();
    ~Renderer();

    void create(luv::Ref<luv::Window> window, luv::Ref<luv::Camera> camera);
    
    bool get_vsync() const;
    void set_vsync(bool vsync);
    
    void set_background_color(Color color);
    
    luv::Ref<luv::Texture> load_texture(const char* path);

    void begin_render();
    void render_texture(const Ref<Texture>& texture, int x, int y, int width, int height);
    void render_sprite(const luv::Ref<luv::Renderable>& renderable);
    void render_quad(luv::Rect rect, std::array<luv::Color, 4> vertexColors);
    void render_quad(luv::Rect rect, luv::Color color);
    void end_render();
  };
}
