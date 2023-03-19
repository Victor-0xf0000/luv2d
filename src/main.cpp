#include <luv2d.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, const char** argv)
{
  luv::Engine engine;
  engine.start();
  engine.getWindow()->change_title("Luvely test");
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
			engine.getCamera()->move_world_pos({500*static_cast<float>(dt), 0.f});
		if (ev.keyEvent.get_key(luv::KeyCode::A) == luv::KeyState::KEY_HOLD)
			engine.getCamera()->move_world_pos({-500*static_cast<float>(dt), 0.f});
		if (ev.keyEvent.get_key(luv::KeyCode::W) == luv::KeyState::KEY_HOLD)
			engine.getCamera()->move_world_pos({0.f, -500*static_cast<float>(dt)});
		if (ev.keyEvent.get_key(luv::KeyCode::S) == luv::KeyState::KEY_HOLD)
			engine.getCamera()->move_world_pos({0.f, 500*static_cast<float>(dt)});
    if (ev.keyEvent.get_key(luv::KeyCode::O) == luv::KeyState::KEY_HOLD)
      engine.getCamera()->change_zoom(-5.f*static_cast<float>(dt));
    if (ev.keyEvent.get_key(luv::KeyCode::P) == luv::KeyState::KEY_HOLD)
      engine.getCamera()->change_zoom(5.f*static_cast<float>(dt));

    if (ev.mouseEvent.get_button(luv::MouseButton::BUTTON_LEFT) == 
        luv::MouseButtonState::MOUSE_BUTTON_HOLD)
    {
      x = ev.mouseEvent.mouse_x;
      y = ev.mouseEvent.mouse_y;
      luv::Rect mpos_to_world = engine.getCamera()->convert_rect_to_world({{x, y}, 1, 1});
      x = mpos_to_world.pos.x;
      y = mpos_to_world.pos.y;
    }
    
		time = time + luv::Time::seconds(dt);
    if (time.get_seconds() > 3.f)
    {
      printf("fps: %f\n", 1.f/dt);
      time = luv::Time::seconds(0.f);
    }
		engine.getRenderer()->set_background_color({147, 157, 173, 255});
		engine.getRenderer()->begin_render();
    
    // Slow
    //engine.getRenderer()->render_quad(camera.convert_rect_to_screen({{0,0}, 
    //    engine.getWindow()->get_width(), engine.getWindow()->get_height()}),
    //    {30, 30, 30, 255});
    for (int i = 0; i < 60; i++)
    {
      engine.getRenderer()->render_texture(texture, 
          i*20, 0, 128, 128);
      engine.getRenderer()->render_texture(texture, 
          i*40, 0, 128, 128);
    }
    engine.getRenderer()->end_render();
	}

  return 0;
}
