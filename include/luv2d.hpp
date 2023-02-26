// SDL2
// TODO: remove sdl2 header, user shouldn't want to use sdl
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
// graphics
#include <engine/graphics/renderer.hpp>
// events
#include <engine/events/keyEvent.hpp>
#include <engine/events/event.hpp>
#include <engine/events/eventManager.hpp>
// core
#include <engine/core/keys.hpp>
#include <engine/core/mouse.hpp>
// engine
#include <engine/engine.hpp>
#include <engine/window.hpp>
