#include <luv2d.hpp>
#include <stdio.h>

int main(int argc, const char** argv)
{
  luv::Engine engine;
  engine.start();
  engine.getWindow()->change_title("LOVELY TEST");
  engine.getWindow()->set_resizable(false);
    
  bool should_quit = false;
  while (!should_quit)
  {  
    luv::Event ev = engine.getEventManager()->getEvent();
    
    engine.getEventManager()->update_events();
    
    if (ev.containsType(luv::EventType::WindowResize))
    {
      printf("new width: %i, new height: %i\n", 
          ev.appEvent.new_width, ev.appEvent.new_height);
    }
    if (ev.containsType(luv::EventType::WindowClose))
    {
      should_quit = true;
    }
    if (ev.keyEvent.get_key(luv::KeyCode::A) == luv::KeyState::KEY_RELEASED)
    {
      printf("a\n");
    }
    if (ev.containsType(luv::EventType::MouseMove))
    {
      printf("x: %i, y: %i\n", ev.mouseEvent.mouse_x, ev.mouseEvent.mouse_y);
    }
  }

  return 0;
}
