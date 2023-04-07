#include <engine/core/clock.hpp>

#include <engine/core/time.hpp>

#include <SDL2/SDL.h>

luv::Clock::Clock()
{
}

void luv::Clock::create()
{
  this->dt = Time::seconds(0.f); 
  this->lt = Time::seconds(0.f);
  this->currTime = Time::seconds((u64)SDL_GetPerformanceCounter());
}

luv::Time luv::Clock::getDeltaTime() const
{
  return this->dt;
}

luv::Time luv::Clock::getCurrTime() const
{
  return this->currTime;
}

void luv::Clock::tick()
{
  this->lt = this->currTime;
  
  this->currTime = Time::seconds((u64)SDL_GetPerformanceCounter());
  
  luv::Time dtt = this->currTime - this->lt;

  u64 dtmilli = dtt.get_milliseconds()/SDL_GetPerformanceFrequency();

  this->dt = Time::milliseconds(dtmilli);
}
