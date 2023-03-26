#include <engine/graphics/renderer.hpp>
#include <engine/graphics/color.hpp>
#include <engine/graphics/texture.hpp>
#include <engine/graphics/renderable.hpp>

#include <engine/core/camera.hpp>
#include <engine/window.hpp>
#include <engine/base.hpp>

#include <SDL2/SDL_Image.h>

luv::Renderer::Renderer()
{
  
}

luv::Renderer::~Renderer()
{
}

void luv::Renderer::create(Ref<luv::Window> window, Ref<luv::Camera> camera)
{
  this->window_ptr = window;
  this->camera_ptr = camera;
  
  this->camera_ptr->set_max_zoom(3.f);
  this->camera_ptr->set_min_zoom(0.7f);

  this->vsync = true;
  this->background_color = luv::Color(40, 40, 40, 255);
  
  this->cmd_count = 0;

  this->sdl_renderer_ptr = SDL_CreateRenderer(
      this->window_ptr->get_sdl_window(), -1, SDL_RENDERER_ACCELERATED);
}

bool luv::Renderer::get_vsync() const
{
  return this->vsync;
}

void luv::Renderer::set_vsync(bool vsync)
{
  this->vsync = vsync;
  // TODO: Save vsync state
  //if (SDL_GL_SetSwapInterval(vsync == true ? 1 : 0) != 0)
  //{
  //  printf("Failed setting vsync! Error: %s\n", SDL_GetError());
  //}
  //else
  //{
  //  this->vsync = vsync;
  //}
}


void luv::Renderer::set_background_color(Color color)
{
  this->background_color = color;
}

luv::Ref<luv::Texture> luv::Renderer::load_texture(const char* path)
{
  luv::Ref<luv::Texture> texture = luv::createRef<luv::Texture>();
  if (!texture->loadFromFile(this->sdl_renderer_ptr, path))
    return nullptr;
  return texture;
}

void luv::Renderer::begin_render()
{
  SDL_SetRenderDrawColor(this->sdl_renderer_ptr, this->background_color.r, this->background_color.g, 
      this->background_color.b, this->background_color.a);
  SDL_RenderClear(this->sdl_renderer_ptr);
}

void luv::Renderer::render_texture(const luv::Ref<luv::Texture>& texture, int x, int y, int width, int height)
{
  luv::Rect rect = this->camera_ptr->convert_rect_to_screen(
      {x, y, width, height});
  SDL_Rect src {0, 0, width, height};
  SDL_Rect dst {rect.pos.x, rect.pos.y, rect.width, rect.height};
  SDL_RenderCopy(this->sdl_renderer_ptr, texture->sdl_texture_ptr, &src, &dst);
}

void luv::Renderer::render_sprite(const luv::Ref<luv::Renderable>& renderable)
{
  this->push_command(renderable->generate_command(this->camera_ptr,
        this->window_ptr->get_width(),
        this->window_ptr->get_height()
  ));
}

void luv::Renderer::render_quad(luv::Rect rect, std::array<luv::Color, 4> vertexColors)
{
}

void luv::Renderer::render_quad(luv::Rect rect, luv::Color color)
{
  luv::Rect screenRect = this->camera_ptr->convert_rect_to_screen(
      {rect.pos.x, rect.pos.y, rect.width, rect.height});
  SDL_Rect dst {screenRect.pos.x, screenRect.pos.y, screenRect.width, screenRect.height};
  SDL_SetRenderDrawBlendMode(this->sdl_renderer_ptr, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(this->sdl_renderer_ptr, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(this->sdl_renderer_ptr, &dst);
}

void luv::Renderer::end_render()
{
  this->run_queue();
  SDL_RenderPresent(this->sdl_renderer_ptr);
}

void luv::Renderer::pop_command()
{
  this->render_commands.pop_back();
  this->cmd_count--;
}

void luv::Renderer::push_command(luv::RenderCmd command)
{
  this->render_commands.push_back(command);
  this->cmd_count++;
}

void luv::Renderer::run_queue()
{
  for (int i = 0; i < this->cmd_count; i++)
  {
    auto cmd = this->render_commands[i];
    
    this->render_texture(cmd.texture, 
        cmd.pos.x, cmd.pos.y,
        cmd.size.x*cmd.scale.x,cmd.size.y*cmd.scale.y);
  }
  this->cmd_count = 0;
  this->render_commands.clear();
}
