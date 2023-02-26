#include <SDL2/SDL.h>

#include <engine/events/keyEvent.hpp>

#include <algorithm>

#include <iostream>

void luv::KeyEvent::create()
{
  std::fill(this->keyCodes.begin(), this->keyCodes.end(), 0);
  std::fill(this->prevKeyCodes.begin(), this->prevKeyCodes.end(), 0);
}

void luv::KeyEvent::update_state()
{
  this->prevKeyCodes = this->keyCodes;

  u8* sdl_array = (u8*) SDL_GetKeyboardState(NULL);
  std::copy(sdl_array, sdl_array+SDL_NUM_SCANCODES, this->keyCodes.begin());
}

luv::KeyState luv::KeyEvent::get_key(KeyCode keyCode)
{
  if (!this->prevKeyCodes[keyCode] && this->keyCodes[keyCode])
    return KeyState::KEY_PRESSED;
  if (this->prevKeyCodes[keyCode] && this->keyCodes[keyCode])
    return KeyState::KEY_HOLD;
  if (this->prevKeyCodes[keyCode] && !this->keyCodes[keyCode])
    return KeyState::KEY_RELEASED;
  if (!this->prevKeyCodes[keyCode] && !this->keyCodes[keyCode])
    return KeyState::KEY_RELEASE;
  return KeyState::KEY_NULL;
}
