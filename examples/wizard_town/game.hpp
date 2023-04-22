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
  
  // Level editor
  bool tilling;
  bool erasing;
  int currSSX;
  int currSSY;
  float ttdtsp; // Time to disappear tilesheet preview, great name isn't it?

  int fps;
public:
  void onStart() override;
  void onTick() override;
  void onRender() override;
};
