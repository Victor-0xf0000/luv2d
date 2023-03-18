#include <luv2d.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, const char** argv)
{
  luv::Engine engine;
  engine.start();
  engine.getWindow()->change_title("LOVELY TEST");
  engine.getWindow()->set_resizable(false);
  engine.getRenderer()->set_vsync(true);  

  bool should_quit = false;
  float x = 0, y = 0;
  luv::Time time = luv::Time::seconds(0.f);
  luv::Ref<luv::Texture> texture = luv::createRef<luv::Texture>();
  texture->loadFromFile("data/test.png");

  while (!should_quit)
  { 
    engine.getClock()->tick();
  
    luv::Event ev = engine.getEventManager()->getEvent();
    
    double dt = engine.getClock()->getDeltaTime().get_seconds();

    if (ev.containsType(luv::EventType::WindowResize))
    {
      printf("new width: %i, new height: %i\n", 
          ev.appEvent.new_width, ev.appEvent.new_height);
    }
    if (ev.containsType(luv::EventType::WindowClose) ||
        ev.keyEvent.get_key(luv::KeyCode::ESCAPE) == luv::KeyState::KEY_PRESSED)
    {
      should_quit = true;
    }
		if (ev.keyEvent.get_key(luv::KeyCode::D) == luv::KeyState::KEY_HOLD)
			x+= 250*dt;
		if (ev.keyEvent.get_key(luv::KeyCode::A) == luv::KeyState::KEY_HOLD)
			x-= 250*dt;
		if (ev.keyEvent.get_key(luv::KeyCode::W) == luv::KeyState::KEY_HOLD)
			y-= 250*dt;
		if (ev.keyEvent.get_key(luv::KeyCode::S) == luv::KeyState::KEY_HOLD)
			y+= 250*dt;
    if (ev.mouseEvent.get_button(luv::MouseButton::BUTTON_LEFT) == 
        luv::MouseButtonState::MOUSE_BUTTON_HOLD)
    {
      x = ev.mouseEvent.mouse_x;
      y = ev.mouseEvent.mouse_y;
    }
    
		time = time + luv::Time::seconds(dt);
    if (time.get_seconds() > 3.f)
    {
      printf("fps: %f\n", 1.f/dt);
      time = luv::Time::seconds(0.f);
    }
		engine.getRenderer()->set_background_color({147, 157, 173, 255});
		engine.getRenderer()->begin_render();
    
    std::array<luv::Color, 4> colors = {
      luv::Color(255, 0, 0, 255), luv::Color(0, 255, 0, 255), 
      luv::Color(0, 0, 255, 255), luv::Color(255, 255, 255, 255)};
    engine.getRenderer()->render_quad({{0, 0}, 
        100, 
        100}, colors);  
    engine.getRenderer()->render_texture(texture, x, y, 256, 256);
    engine.getRenderer()->render_texture(texture, 300, 250, 256, 256);

    engine.getRenderer()->end_render();
	}

  return 0;
}
