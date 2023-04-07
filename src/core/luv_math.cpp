#include <engine/core/luv_math.hpp>

float luv::absf(float n)
{
  if (n < 0.f)
    return -n;
  return n;
}
