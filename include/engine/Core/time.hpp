#pragma once

#include <engine/base.hpp>

namespace luv
{
  struct Time
  {
  private:
    u64 in_milliseconds;
  public:
    static Time seconds(double seconds)
    {
      Time t;
      t.in_milliseconds = (u64)(seconds*1000);
      return t;
    }

    static Time milliseconds(u64 milliseconds)
    {
      Time t;
      t.in_milliseconds = milliseconds;
      return t;
    }

    double get_seconds()
    {
      return static_cast<double>(this->in_milliseconds)/1000.f;
    }

    u64 get_milliseconds()
    {
      return this->in_milliseconds;
    }

    Time operator-(Time const &t2)
    {
      return Time::milliseconds(this->in_milliseconds-t2.in_milliseconds);
    }

    Time operator+(Time const& t2)
    {
      return Time::milliseconds(this->in_milliseconds+t2.in_milliseconds);
    }
  };
}
