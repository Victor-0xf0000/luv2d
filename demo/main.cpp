#include <luv2d.hpp>
#include <stdio.h>
#include <iostream>
#include <string>

void screenCollision(luv::Rect* rect, int ww, int wh)
{
  if (rect->pos.x + rect->width > ww)
    rect->pos.x = ww - rect->width;
  if (rect->pos.x < 0.f)
    rect->pos.x = 0.f;

  if (rect->pos.y + rect->height > wh)
    rect->pos.y = wh - rect->height;
  if (rect->pos.y < 0.f)
    rect->pos.y = 0.f;
}

void screenBallCollision(luv::Rect* ball, luv::vec2f* bdir, int ww, int wh)
{
  if (ball->pos.x + ball->width > ww)
  {
    ball->pos.x = ww - ball->width;
    bdir->x *= -1.f;
  }
  if (ball->pos.x < 0.f)
  {
    ball->pos.x = 0.f;
    bdir->x *= -1.f;
  }

  if (ball->pos.y + ball->height > wh)
  {
    ball->pos.y = wh - ball->width;
    bdir->y *= -1.f;
  } 
  if (ball->pos.y < 0.f)
  {
    ball->pos.y = 0.f;
    bdir->y *= -1.f;
  } 
}

void ballPaddleCollision(luv::Rect* ball, luv::vec2f* bdir, luv::Rect paddle)
{
  if (ball->pos.y + ball->width > paddle.pos.y && 
      ball->pos.y < paddle.pos.y + paddle.height)
  {
    if (ball->pos.x < paddle.pos.x + paddle.width &&
        ball->pos.x + ball->width > paddle.pos.x)
    {
      if (bdir->x < 0.f)
        ball->pos.x = paddle.pos.x + paddle.width + 1.f;
      if (bdir->x > 0.f)
        ball->pos.x = paddle.pos.x - ball->width - 1.f;
      bdir->x *= -1.f;
    }
  }
}

struct Game :
  public luv::Application
{
private:
  luv::Rect p1;
  luv::Rect p2;
  luv::Rect ball;
  luv::vec2f bdir;
  luv::Time time;
public:
  void onStart() override
  {
    this->time = luv::Time::seconds(0.f);
    
    int ww = this->Window()->get_width(), wh = this->Window()->get_height();
    this->p1 = {{0.f, 0.f}, 32, wh/4};
    this->p2 = {{ww-32.f, 0.f}, 32, wh/4};
    this->ball = {{ww/2.f,wh/2.f}, 32,32};
    this->bdir = {-1.f, 1.f};
    this->Camera()->set_world_pos({ww/2, wh/2});
  }
  
  void onTick() override
  {
    luv::Event ev = this->EventManager()->getEvent();
    double dt = this->Clock()->getDeltaTime().get_seconds();

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
      this->p1.pos.y -= 500.f * dt;
    if (ev.keyEvent.get_key(luv::KeyCode::S) == luv::KeyState::KEY_HOLD)
      this->p1.pos.y += 500.f * dt;
    if (ev.keyEvent.get_key(luv::KeyCode::E) == luv::KeyState::KEY_HOLD)
      this->p2.pos.y -= 500.f * dt;
    if (ev.keyEvent.get_key(luv::KeyCode::D) == luv::KeyState::KEY_HOLD)
      this->p2.pos.y += 500.f * dt;
    int ww = this->Window()->get_width(), wh = this->Window()->get_height();
    this->ball.pos.x += this->bdir.x * 300.f * dt;
    this->ball.pos.y += this->bdir.y * 300.f * dt;

    screenCollision(&this->p1, ww, wh);
    screenCollision(&this->p2, ww, wh);
		screenBallCollision(&this->ball, &this->bdir, ww, wh);
    ballPaddleCollision(&this->ball, &this->bdir, this->p1);
    ballPaddleCollision(&this->ball, &this->bdir, this->p2);

    time = time + luv::Time::seconds(dt);
    if (time.get_seconds() > 3.f)
    {
      printf("fps: %f\n", 1.f/dt);
      time = luv::Time::seconds(0.f);
    }

		this->Renderer()->set_background_color({40, 40, 40, 255});
		this->Renderer()->begin_render();
    this->Renderer()->render_quad(this->p1, {120, 120, 120, 255});
    this->Renderer()->render_quad(this->p2, {120, 120, 120, 255});
    this->Renderer()->render_quad(this->ball, {120, 120, 120, 255});
    this->Renderer()->end_render();
  }
};

int main(int argc, char** argv)
{
  luv::Scope<Game> game = luv::createScope<Game>();
  
  game->init();
  
  return 0;
}
