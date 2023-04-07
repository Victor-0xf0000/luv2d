#include <luv2d.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>

const int tile_size_x = 16;
const int tile_size_y = 12;

struct Game :
  public luv::Application
{
private:
  std::vector<luv::vec2f> body;
  int sw, sh;
  luv::vec2f dir;
  luv::vec2f apple;
  int bodySize;
  luv::Time time;
  luv::Time rateTime;
public:
  void onStart() override
  {
    srand(123123);
    this->body = std::vector<luv::vec2f>();
    this->time = luv::Time::seconds(0.f);
    this->rateTime = luv::Time::milliseconds(0);
    this->sw = 32;
    this->sh = 32;
    this->bodySize = 4;
    this->dir = {0.f, 0.f};
    this->apple = {0.f, 0.f};
    
    // WTF ?
    this->Window()->set_resizable(true);
    this->Window()->resize(this->sw*tile_size_x, this->sh*tile_size_y);
    this->Window()->set_resizable(false);

    for (int i = 0; i < this->bodySize; i++)
    {
      this->body.push_back({0.f, 0.f});
    }

    int ww = this->Window()->get_width(), wh = this->Window()->get_height();
    this->Camera()->set_world_pos({ww/2.f, wh/2.f});
    this->Camera()->set_min_zoom(0.5f);
  }
  
  void onTick() override
  {
    luv::Event ev = this->EventManager()->getEvent();
    double dt = this->Clock()->getDeltaTime().get_seconds();
    
    auto rangen = [](int min, int max) -> int{
      int ret = (rand() % (max+1)) + min;
      return ret;
    };    

    if (ev.containsType(luv::EventType::WindowResize))
    {
      printf("new width: %i, new height: %i\n", 
          ev.appEvent.new_width, ev.appEvent.new_height);
    }
    if (ev.containsType(luv::EventType::WindowClose) ||
        ev.keyEvent.get_key(luv::KeyCode::ESCAPE) == luv::KeyState::KEY_PRESSED)
    {
      this->quit();
    }

    if (ev.keyEvent.get_key(luv::KeyCode::W) == luv::KeyState::KEY_HOLD)
      this->dir = {0.f, -1.f};
    if (ev.keyEvent.get_key(luv::KeyCode::S) == luv::KeyState::KEY_HOLD)
      this->dir = {0.f, 1.f};
    if (ev.keyEvent.get_key(luv::KeyCode::A) == luv::KeyState::KEY_HOLD)
      this->dir = {-1.f, 0.f};
    if (ev.keyEvent.get_key(luv::KeyCode::D) == luv::KeyState::KEY_HOLD)
      this->dir = {1.f, 0.f};

    if (ev.keyEvent.get_key(luv::KeyCode::J) == luv::KeyState::KEY_HOLD)
      this->Camera()->move_world_pos({-500*dt, 0.f});
    if (ev.keyEvent.get_key(luv::KeyCode::L) == luv::KeyState::KEY_HOLD)
      this->Camera()->move_world_pos({500*dt, 0.f});
    if (ev.keyEvent.get_key(luv::KeyCode::K) == luv::KeyState::KEY_HOLD)
      this->Camera()->move_world_pos({0.f, 500*dt});
    if (ev.keyEvent.get_key(luv::KeyCode::I) == luv::KeyState::KEY_HOLD)
      this->Camera()->move_world_pos({0.f, -500*dt});
    
    if (ev.keyEvent.get_key(luv::KeyCode::O) == luv::KeyState::KEY_HOLD)
      this->Camera()->change_zoom(-10.f*dt);
    if (ev.keyEvent.get_key(luv::KeyCode::P) == luv::KeyState::KEY_HOLD)
      this->Camera()->change_zoom(10.f*dt);

    this->rateTime = this->rateTime + luv::Time::seconds(dt);
    if (this->rateTime.get_milliseconds() > 50)
    {
      if (this->body[0].x == this->apple.x && this->body[0].y == this->apple.y)
      {
        this->apple = {rangen(0, tile_size_x-1), rangen(0, tile_size_y-1)};
        auto const back = this->body.back();
        this->body.push_back({
            back.x,
            back.y
            });
        this->bodySize++;
      }
      for (auto i = this->bodySize-1; i != 0; i--)
      {
        this->body[i].x = this->body[i-1].x;
        this->body[i].y = this->body[i-1].y;
        if (this->body[0].x+this->dir.x == this->body[i].x && 
            this->body[0].y+this->dir.y == this->body[i].y)
        {
          this->bodySize = 4;
          this->body.clear();
          for (int i = 0; i < this->bodySize; i++)
            this->body.push_back({0.f,0.f});
          this->dir = {0.f,0.f};
        }
      }
      this->body[0].x += this->dir.x;
      this->body[0].y += this->dir.y;
      
      if (this->body[0].x >= tile_size_x)
        this->body[0].x = 0;
      if (this->body[0].y >= tile_size_y)
        this->body[0].y = 0;
      if (this->body[0].x < 0)
        this->body[0].x = tile_size_x-1;
      if (this->body[0].y < 0)
        this->body[0].y = tile_size_y-1;

      this->rateTime = luv::Time::milliseconds(0);
    }
    int ww = this->Window()->get_width(), wh = this->Window()->get_height();

    time = time + luv::Time::seconds(dt);
    if (time.get_seconds() > 3.f)
    {
      printf("fps: %f\n", 1.f/dt);
      time = luv::Time::seconds(0.f);
    }

  }

  void onRender() override
  {
		this->Renderer()->set_background_color({40, 40, 40, 255});
    for (const auto& part : this->body)
    {
      this->Renderer()->render_quad({{
          part.x*sw, // snake width and snake height
          part.y*sh
          }, sw, sh
          }, 
          {120, 120, 120, 255});
    } 
    this->Renderer()->render_quad({
        {this->apple.x*sw,
        this->apple.y*sh}, sw, sh}, {90, 30, 30, 255});
    this->Renderer()->render_quad({{0.f, 0.f}, 
        this->Window()->get_width(), 
        this->Window()->get_height()}, {255,255,255,30});
  }
};

int main(int argc, char** argv)
{
  luv::Scope<Game> game = luv::createScope<Game>();
  
  game->init();
  
  return 0;
}
