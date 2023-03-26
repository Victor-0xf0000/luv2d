#include <luv2d.hpp>
#include <stdio.h>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
  luv::Engine engine;
  engine.start();
  engine.getWindow()->change_title("luvely test");
  engine.getWindow()->set_resizable(false);
  engine.getRenderer()->set_vsync(true);  
  engine.getCamera()->set_min_zoom(0.7f);
  bool should_quit = false;
  float x = 0, y = 0;
  luv::Time time = luv::Time::seconds(0.f);
  
  engine.getAssetsManager()->loadTextures({
      {"test", "data/test.png"},
      {"test2", "data/test2.png"}
  });
  
  luv::Ref<luv::Renderable> renderable = luv::createRef<luv::Renderable>();
  renderable->set_texture(engine.getAssetsManager()->getTexture("test2"));
  renderable->set_size({64.f, 64.f});
  renderable->set_pos({0.f, 0.f});
  renderable->set_scale({2.f, 2.f});
  
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
    if (ev.keyEvent.get_key(luv::KeyCode::R) == luv::KeyState::KEY_PRESSED)
      engine.getCamera()->change_zoom(1.f);

    if (ev.mouseEvent.get_button(luv::MouseButton::BUTTON_LEFT) == 
        luv::MouseButtonState::MOUSE_BUTTON_HOLD)
    {
      x = ev.mouseEvent.mouse_x;
      y = ev.mouseEvent.mouse_y;
      luv::Rect mpos_to_world = engine.getCamera()->convert_rect_to_world({{x, y}, 1, 1});
      x = mpos_to_world.pos.x;
      y = mpos_to_world.pos.y;
      renderable->set_pos({x, y});
    }
    if (ev.keyEvent.get_key(luv::KeyCode::NUMBER_1) == luv::KeyState::KEY_PRESSED)
      renderable->set_texture(engine.getAssetsManager()->getTexture("test"));
    if (ev.keyEvent.get_key(luv::KeyCode::NUMBER_2) == luv::KeyState::KEY_PRESSED)
      renderable->set_texture(engine.getAssetsManager()->getTexture("test2"));
    
		time = time + luv::Time::seconds(dt);
    if (time.get_seconds() > 3.f)
    {
      printf("fps: %f\n", 1.f/dt);
      time = luv::Time::seconds(0.f);
    }
		engine.getRenderer()->set_background_color({40, 40, 40, 255});
		engine.getRenderer()->begin_render();
    
    engine.getRenderer()->render_quad({{0, 0}, 
        engine.getWindow()->get_width(), engine.getWindow()->get_height()},
        {50, 50, 50, 255});
    engine.getRenderer()->render_sprite(renderable);
    engine.getRenderer()->end_render();
	}

  return 0;
}
