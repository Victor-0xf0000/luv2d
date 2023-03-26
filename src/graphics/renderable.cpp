#include <engine/graphics/renderable.hpp>
#include <engine/graphics/texture.hpp>

#include <engine/core/luv_math.hpp>
#include <engine/core/camera.hpp>

luv::Renderable::Renderable()
{
  //this->texture = luv::createRef<luv::Texture>();   
  this->texture = nullptr;
  this->pos = {0.f, 0.f};
  this->scale = {1.f, 1.f};
  this->size = {0.f, 0.f};
}

luv::Renderable::~Renderable()
{
  
}

luv::RenderCmd luv::Renderable::generate_command(luv::Ref<luv::Camera> camera, 
    int window_width, int window_height)
{
  //luv::Rect screen_rect = camera->convert_rect_to_screen(
  //    {{this->pos.x, this->pos.y}, 
  //    this->size.x*this->scale.x, this->size.y*this->scale.y}
  //);
  //
  //float ww = (float) window_width;
  //float wh = (float) window_height;

  //luv::Geometry geometry;
  //geometry.vertexData = new VertexData[4];
  //
  //float norm_x = (screen_rect.pos.x / ww) * 2.f - 1.f;
  //float norm_y = 1.f - (screen_rect.pos.y / wh) * 2.f;
  ////float norm_w = this->screen_rect.size.x * this->scale.x / ww;
  ////float norm_h = this->screen_rect.size.y * this->scale.y / wh;
  //float norm_w = screen_rect.width  / ww;
  //float norm_h = screen_rect.height / wh;
  //
  //geometry.vertexData[0] = {
  //  {norm_x,norm_y},                      {0.f,0.f},{255, 255, 255, 255}};
  //
  //geometry.vertexData[1] = {
  //  {norm_x+norm_w*2.f, norm_y},          {1.f,0.f},{255, 255, 255, 255}};
  //
  //geometry.vertexData[2] = {
  //  {norm_x+norm_w*2.f,norm_y-norm_h*2.f},{1.f,1.f},{255, 255, 255, 255}};
  //
  //geometry.vertexData[3] = {
  //  {norm_x,norm_y-norm_h*2.f},           {0.f,1.f},{255, 255, 255, 255}};
  //
  //geometry.vertex_count = 4;

  //luv::RenderCmd rendercmd;
  //rendercmd.texture = this->texture;
  //rendercmd.geometry = geometry;
  
  luv::RenderCmd rendercmd;
  rendercmd.texture = this->texture;
  rendercmd.pos = this->pos;
  rendercmd.size = this->size;
  rendercmd.scale = this->scale;

  return rendercmd;  
}

void luv::Renderable::set_texture(luv::Ref<luv::Texture> texture) 
{
  this->texture = texture;
}

void luv::Renderable::set_size(luv::vec2f size)
{
  this->size = size;
}

void luv::Renderable::set_pos(luv::vec2f pos)
{
  this->pos.x = pos.x;
  this->pos.y = pos.y;
}

void luv::Renderable::set_scale(luv::vec2f scale)
{
  this->scale = scale;
}
