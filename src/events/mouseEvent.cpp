#include <engine/events/mouseEvent.hpp>
#include <engine/core/mouse.hpp>

#include <SDL2/SDL.h>

void luv::MouseEvent::create()
{
  for (int i = 0; i < 3; i++)
  {
    this->mouseButtons[i] = -1;
    this->prevMouseButtons[i] = -1;
  }
}
      
void luv::MouseEvent::update_state()
{
  this->prevMouseButtons = this->mouseButtons;
  int x, y;
  SDL_GetMouseState(&x, &y);
  this->mouse_x = x;
  this->mouse_y = y;
}
      
luv::MouseButtonState luv::MouseEvent::get_button(luv::MouseButton button)
{
  int index = (int) button;
  if (!this->prevMouseButtons[index] && this->mouseButtons[index])
    return luv::MouseButtonState::MOUSE_BUTTON_PRESSED;
  if (this->prevMouseButtons[index] && this->mouseButtons[index])
    return luv::MouseButtonState::MOUSE_BUTTON_HOLD;
  if (this->prevMouseButtons[index] && !this->mouseButtons[index])
    return luv::MouseButtonState::MOUSE_BUTTON_RELEASED;
  if (!this->prevMouseButtons[index] && !this->mouseButtons[index])
    return luv::MouseButtonState::MOUSE_BUTTON_RELEASE;
  return luv::MouseButtonState::MOUSE_BUTTON_NULL;
}
