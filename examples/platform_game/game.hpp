#pragma once

#include <luv2d.hpp>
#include <entt/entt.hpp>
#include <tileset.hpp>

struct Game : public luv::Application
{
private:
  luv::Time time;
  luv::Ref<TileSet> tileset;

  entt::registry registry;

  luv::Ref<luv::Font> arialf;
public:
  void onStart() override;
  void onTick() override;
  void onRender() override;
};
