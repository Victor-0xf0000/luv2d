#pragma once

#include <luv2d.hpp>
#include <entt/entt.hpp>
#include <tileset.hpp>
#include <rooms.hpp>
#include <uiSystem.hpp>

struct Game : public luv::Application
{
private:
  luv::Time time;
  luv::Ref<Rooms> rooms;
  luv::Ref<UiSystem> uiSystem;
  luv::Ref<luv::Font> arialf;

  bool tilling;
  bool erasing;

  int fps;
public:
  void onStart() override;
  void onTick() override;
  void onRender() override;
};
