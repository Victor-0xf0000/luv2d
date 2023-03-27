#pragma once

#include <engine/platform.hpp>
#include <engine/base.hpp>
#include <engine/events/applicationEvent.hpp>
#include <engine/events/keyEvent.hpp>
#include <engine/events/mouseEvent.hpp>
#include <string>
#include <bitset>

namespace luv
{
  enum EventCategory
  {
    AppEventCategory = 1,
    KeyEventCategory,
    MouseEventCategory
  };
   
  enum EventType
  {
    WindowResize = 1,
    WindowClose,
    KeyPress,
    KeyRelease,
    MouseButtonPress,
    MouseButtonRelease,
    MouseButtonScroll,
    MouseMove
  };
  
  struct EventManager;

  struct LUV2D_ENGINE_API Event
  {
    friend EventManager;
  private:
    std::bitset<8> eventCategory;
    std::bitset<16> eventType;
  public:
    ApplicationEvent appEvent;
    MouseEvent mouseEvent;
    KeyEvent keyEvent;

    bool containsCategory(EventCategory category)
    {
      return this->eventCategory.test((int)category);
    }

    bool containsType(EventType type)
    {
        return this->eventType.test((int)type);
    }
  };
}
