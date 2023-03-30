#include <engine/events/eventManager.hpp>

#include <SDL2/SDL.h>

luv::EventManager::EventManager()
{

}

luv::EventManager::~EventManager()
{

}

void luv::EventManager::create()
{
  this->event.keyEvent.create();
  this->event.mouseEvent.create();
}

void luv::EventManager::update_events()
{
  this->event.mouseEvent.update_state();
  
  this->event.eventCategory.reset();
  this->event.eventType.reset();
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
        {
          this->event.eventCategory.set((int)EventCategory::AppEventCategory);
          this->event.eventType.set((int)EventType::WindowClose);
        }
        break;
      case SDL_WINDOWEVENT:
      {
        if (e.window.event == SDL_WINDOWEVENT_RESIZED)
        {
          this->event.eventCategory.set((int)EventCategory::AppEventCategory);
          this->event.eventType.set((int)EventType::WindowResize);
          this->event.appEvent.new_width = e.window.data1;
          this->event.appEvent.new_height = e.window.data2;
        }
        break;
      }
      case SDL_KEYDOWN:
      {
        this->event.eventCategory.set((int)EventCategory::KeyEventCategory);
        this->event.eventType.set((int)EventType::KeyPress);
        break;
      }
      case SDL_KEYUP:
      {
        this->event.eventCategory.set((int)EventCategory::KeyEventCategory);
        this->event.eventType.set((int)EventType::KeyRelease);
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
      {
        this->event.eventCategory.set((int)EventCategory::MouseEventCategory);
        this->event.eventType.set((int)EventType::MouseButtonPress);
        if (e.button.button == SDL_BUTTON_LEFT)
          this->event.mouseEvent.mouseButtons[luv::MouseButton::BUTTON_LEFT] = 1;
        else if (e.button.button == SDL_BUTTON_RIGHT)
          this->event.mouseEvent.mouseButtons[luv::MouseButton::BUTTON_RIGHT] = 1;
        else if (e.button.button == SDL_BUTTON_MIDDLE)
          this->event.mouseEvent.mouseButtons[luv::MouseButton::BUTTON_MIDDLE] = 1;
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        this->event.eventCategory.set((int)EventCategory::MouseEventCategory);
        this->event.eventType.set((int)EventType::MouseButtonRelease);
        if (e.button.button == SDL_BUTTON_LEFT)
          this->event.mouseEvent.mouseButtons[luv::MouseButton::BUTTON_LEFT] = 0;
        else if (e.button.button == SDL_BUTTON_RIGHT)
          this->event.mouseEvent.mouseButtons[luv::MouseButton::BUTTON_RIGHT] = 0;
        else if (e.button.button == SDL_BUTTON_MIDDLE)
          this->event.mouseEvent.mouseButtons[luv::MouseButton::BUTTON_MIDDLE] = 0;
        break;
      }
      case SDL_MOUSEWHEEL:
      {
        this->event.eventCategory.set((int)EventCategory::MouseEventCategory);
        this->event.eventType.set((int)EventType::MouseButtonScroll);
        break;
      }
      case SDL_MOUSEMOTION:
      {
        this->event.eventCategory.set((int)EventCategory::MouseEventCategory);
        this->event.eventType.set((int)EventType::MouseMove);
        break;
      }
      default:
        break;
    }
  }
  this->event.keyEvent.update_state();
}

luv::Event luv::EventManager::getEvent()
{
  return this->event;
}
