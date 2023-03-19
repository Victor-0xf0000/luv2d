#include <engine/core/camera.hpp>

#include <stdio.h>
luv::Camera::Camera()
{ 
}

luv::Camera::~Camera()
{ 
    
}

void luv::Camera::create(int window_width, int window_height)
{
  float ratio = (float) window_width / (float) window_height;
  
  this->zoom = 1.f;
  this->ww = window_width;
  this->wh = window_height;
  this->vw = window_width;
  this->vh = window_height;
  this->world_pos = {0.f, 0.f};
}

void luv::Camera::window_resized(int window_width, int window_height)
{
  this->vw = window_width * this->zoom;
  this->vh = window_height * this->zoom;
  this->ww = window_width;
  this->wh = window_height;
}

void luv::Camera::change_zoom(float add)
{
  float nzoom = this->zoom + add;
  if (nzoom > this->max_zoom)
    this->zoom = this->max_zoom;
  else if (nzoom < this->min_zoom)
    this->zoom = this->min_zoom;
  else
    this->zoom = nzoom;
  
  this->vw = this->ww / this->zoom;
  this->vh = this->wh / this->zoom;
}

void luv::Camera::set_max_zoom(float max_zoom)
{
  this->max_zoom = max_zoom;
  this->change_zoom(0.f); // recalculate zoom
}

void luv::Camera::set_min_zoom(float min_zoom)
{
  this->min_zoom = min_zoom;
  this->change_zoom(0.f); // recalculate zoom
}

void luv::Camera::set_world_pos(vec2f pos)
{
  this->world_pos = pos;
}

void luv::Camera::move_world_pos(vec2f diff)
{
  this->world_pos.x += diff.x;
  this->world_pos.y += diff.y;
}

luv::Rect luv::Camera::convert_rect_to_screen(luv::Rect rect)
{
  luv::Rect nrect;
  
  nrect.pos.x = (rect.pos.x) - 
    (this->world_pos.x - static_cast<float>(this->vw)/2.f);
  nrect.pos.y = (rect.pos.y) - 
    (this->world_pos.y - static_cast<float>(this->vh)/2.f);
  nrect.pos.x *= zoom;
  nrect.pos.y *= zoom;
  nrect.width = rect.width * this->zoom;
  nrect.height = rect.height * this->zoom;
  return nrect;
}

// nrectposx = rectposx - worldposx + vw/2
// nrectposx + worldposx - vw/2 = rectposx

luv::Rect luv::Camera::convert_rect_to_world(luv::Rect rect)
{
  luv::Rect nrect;

  nrect.pos.x = rect.pos.x/zoom + 
    (this->world_pos.x - static_cast<float>(this->vw)/2.f);
  nrect.pos.y = rect.pos.y/zoom + 
    (this->world_pos.y - static_cast<float>(this->vh)/2.f);
  nrect.width = rect.width / this->zoom;
  nrect.height = rect.height / this->zoom;
  
  return nrect;
}
