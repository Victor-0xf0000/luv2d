#include <engine/events/applicationEvent.hpp>

void luv::ApplicationEvent::update_state()
{

}

int luv::ApplicationEvent::get_window_width() const
{
  return this->new_width;
}

int luv::ApplicationEvent::get_window_height() const
{
  return this->new_height;
}
