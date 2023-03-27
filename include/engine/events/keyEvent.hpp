#pragma once

#include <SDL2/SDL.h>

#include <engine/Core/keys.hpp>
#include <engine/Base.hpp>
#include <engine/platform.hpp>

#include <array>

namespace luv
{
  struct LUV2D_ENGINE_API KeyEvent
  {
    std::array<u8, SDL_NUM_SCANCODES> keyCodes;
    std::array<u8, SDL_NUM_SCANCODES> prevKeyCodes;
    
    void create();

    void update_state();
    KeyState get_key(KeyCode keyCode);
  };
}
