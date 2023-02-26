#pragma once

#include <engine/base.hpp>
#include <engine/events/applicationEvent.hpp>
#include <engine/events/keyEvent.hpp>
#include <engine/events/mouseEvent.hpp>
#include <string>
#include <bitset>

// Prototype, idk

// -------------------------------
//#include <iostream>
//#include <memory>
//#include <string>
//
//enum eventType
//{
//    windowResize,
//    windowClose,
//    keyPressed,
//    keyReleased,
//    keyHold
//};
//
//struct ApplicationEvent
//{
//    
//}
//
//struct App
//{
//    void event(Event& e)
//    {
//        if (e.containsType(WINDOW_RESIZED))
//        {
//            this->window.width = e.appEvent.new_width;
//            this->window.height = e.appEvent.new_height;
//        }
//        
//        if (e.containsType(KEY_PRESS))
//        {
//            // one time press
//            if (e.keyEvent.wasKeyPressed(KeyCode::e))
//            {
//                
//            }
//            // continous press
//            if (e.keyEvent.isKeyHold(KeyCode::w))
//            {
//                
//            }
//        }
//        // I can ommit e.containsType too
//        if (e.keyEvent.wasKeyReleased(KeyCode::x))
//        {
//            
//        }
//    }
//}
//
//struct Event
//{
//    ApplicationEvent apEvent;
//    KeyEvent keyEvent;
//    MouseEvent mouseEvent;
//};
// --------------------------

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

  struct Event
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
