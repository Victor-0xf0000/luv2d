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
  struct Font;
  struct Renderable;
  
  enum RenderViewMode
  {
    RVM_SCREENVIEW,
    RVM_CAMERAVIEW
  };
  
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
    
    // Will the object be static or follow the camera view
    luv::RenderViewMode renderViewMode;
    
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
    luv::Ref<luv::Font> load_font(const char* path, int size);
    
    void begin_render();
    void render_texture(const Texture* texture, luv::Rect dst);
    void render_texture(const Texture* texture, luv::Rect src, luv::Rect dst);
    void render_sprite(const luv::Ref<luv::Renderable>& renderable);
    void render_quad(luv::Rect rect, luv::Color color);
    void render_text(luv::Font* font, luv::vec2f pos, const char* text);
    void render_quad_text(luv::Font* font, 
        luv::Rect rect, luv::Color rectColor, 
        const char* text, luv::Color textColor);

    void setRenderViewMode(luv::RenderViewMode renderViewMode);
    void end_render();
  };
}
