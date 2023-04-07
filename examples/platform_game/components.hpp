#pragma once

#include <luv2d.hpp>

struct Transform
{
  luv::vec2f pos;
  int width, height;
};

struct SquareSprite
{
  luv::Color color;
};

struct RigidBody
{
  luv::vec2f acc;
};

struct Control
{
  luv::vec2f dir;
};

struct TileCollider
{
  // Hitbox position and size
  luv::vec2f origin;
  int width, height;
};
