#include <engine/graphics/renderer.hpp>
#include <engine/graphics/color.hpp>
#include <engine/graphics/texture.hpp>

#include <engine/core/camera.hpp>
#include <engine/window.hpp>
#include <engine/base.hpp>

#include <SDL2/SDL_Image.h>

#include <glad/glad.h>

luv::Renderer::Renderer()
  : vsync(false)
{
  
}

luv::Renderer::~Renderer()
{
  //SDL_DestroyRenderer(this->sdl_renderer_ptr);
}

void luv::Renderer::create(Ref<luv::Window> window, Ref<luv::Camera> camera)
{
  this->window_ptr = window;
  this->camera_ptr = camera;
  
  this->camera_ptr->set_max_zoom(3.f);

  this->vsync = false;
  this->background_color = luv::Color(40, 40, 40, 255);
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  if (SDL_GL_SetSwapInterval(1) != 0)
  {
    printf("Failed to set vsnyc: %s\n", SDL_GetError());
  }
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool luv::Renderer::get_vsync() const
{
  return this->vsync;
}

void luv::Renderer::set_vsync(bool vsync)
{
  this->vsync = vsync;

  // TODO: Save vsync state
  if (SDL_GL_SetSwapInterval(vsync == true ? 1 : 0) != 0)
  {
    printf("Failed setting vsync! Error: %s\n", SDL_GetError());
  }
}


void luv::Renderer::set_background_color(Color color)
{
  this->background_color = color;
}

void luv::Renderer::begin_render()
{
  glClearColor(this->background_color.norm_r(), 
      this->background_color.norm_g(), 
      this->background_color.norm_b(), 
      this->background_color.norm_a());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void luv::Renderer::render_texture(const luv::Ref<luv::Texture>& texture, int x, int y, int width, int height)
{
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glDisable(GL_DEPTH_TEST);
  glBindTexture(GL_TEXTURE_2D, texture->get_texture_name());
  
  luv::Rect drect = {{x, y}, width, height};
  drect = this->camera_ptr->convert_rect_to_screen(drect);
  
  float ww = (float) this->window_ptr->get_width(); 
  float wh = (float) this->window_ptr->get_height();
  float norm_x = (drect.pos.x / ww)*2-1;
  float norm_y = 1.f-((drect.pos.y) / wh)*2;
  float norm_w = drect.width / ww;
  float norm_h = drect.height / wh;
  
  glColor4f(1.f, 1.f, 1.f, 1.f);
  glBegin(GL_POLYGON);
    glTexCoord2f(0.f, 0.f); glVertex2f(norm_x, norm_y);
    glTexCoord2f(1.f, 0.f); glVertex2f(norm_x + norm_w*2, norm_y);
    glTexCoord2f(1.f, 1.f); glVertex2f(norm_x + norm_w*2, norm_y - norm_h*2);
    glTexCoord2f(0.f, 1.f); glVertex2f(norm_x, norm_y - norm_h*2);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

// Slow, why? Idk
void luv::Renderer::render_quad(luv::Rect rect, std::array<luv::Color, 4> vertexColors)
{
  luv::Rect drect = this->camera_ptr->convert_rect_to_screen(rect);

  float ww = (float) this->window_ptr->get_width(); 
  float wh = (float) this->window_ptr->get_height();
  
  float norm_x = (drect.pos.x / ww)*2-1;
  float norm_y = 1.f-((drect.pos.y) / wh)*2;
  
  float norm_w = (float) drect.width / ww;
  float norm_h = (float) drect.height / wh;
  
  glBegin(GL_POLYGON);
    glColor4f(vertexColors[0].norm_r(), vertexColors[0].norm_g(), vertexColors[0].norm_b(), vertexColors[0].norm_a());
    glVertex3f(norm_x, norm_y, 0);
    glColor4f(vertexColors[1].norm_r(), vertexColors[1].norm_g(), vertexColors[1].norm_b(), vertexColors[1].norm_a());
    glVertex3f(norm_x + norm_w*2, norm_y, 0);
    glColor4f(vertexColors[2].norm_r(), vertexColors[2].norm_g(), vertexColors[2].norm_b(), vertexColors[2].norm_a());
    glVertex3f(norm_x + norm_w*2, norm_y - norm_h*2, 0);
    glColor4f(vertexColors[3].norm_r(), vertexColors[3].norm_g(), vertexColors[3].norm_b(), vertexColors[3].norm_a());
    glVertex3f(norm_x, norm_y - norm_h*2, 0);
  glEnd();
}

// Slow too
void luv::Renderer::render_quad(luv::Rect rect, luv::Color color)
{
  luv::Rect drect = this->camera_ptr->convert_rect_to_screen(rect);

  float ww = (float) this->window_ptr->get_width(); 
  float wh = (float) this->window_ptr->get_height();
  
  float norm_x = (drect.pos.x / ww)*2-1;
  float norm_y = 1.f-((drect.pos.y) / wh)*2;
  
  float norm_w = drect.width / ww;
  float norm_h = drect.height / wh;

  glShadeModel(GL_FLAT);
  glDisable(GL_POLYGON_SMOOTH);
  glDisable(GL_DEPTH_TEST);
  glColor4f(color.norm_r(), color.norm_g(), color.norm_b(), color.norm_a());
  glBegin(GL_POLYGON);
    glVertex2f(norm_x, norm_y);
    glVertex2f(norm_x + norm_w*2, norm_y);
    glVertex2f(norm_x + norm_w*2, norm_y - norm_h*2);
    glVertex2f(norm_x, norm_y - norm_h*2);
  glEnd();
}

void luv::Renderer::end_render()
{
  glFlush();
  SDL_GL_SwapWindow(this->window_ptr->get_sdl_window());
}
