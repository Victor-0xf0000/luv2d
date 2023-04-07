#pragma once

#include <entt/entt.hpp>
#include <components.hpp>
#include <luv2d.hpp>

namespace player
{
  entt::entity create(luv::AssetsManager* assetsManager, 
      entt::registry& registry, luv::vec2f pos)
  {
    auto player = registry.create();
    registry.emplace<Transform>(player, pos, 40, 60);
    registry.emplace<SquareSprite>(player);
    registry.emplace<Control>(player, 0.f, 0.f);
    registry.emplace<TileCollider>(player, 0.f, 0.f, 40, 60);
    registry.get<SquareSprite>(player).color = 
      luv::Color(50, 60, 80, 255);

    return player;
  }   
}
