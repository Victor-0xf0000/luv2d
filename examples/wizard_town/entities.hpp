#pragma once

#include <entt/entt.hpp>
#include <components.hpp>
#include <luv2d.hpp>

namespace entities
{
  entt::entity playerCreate( 
      entt::registry& registry, luv::AssetsManager* am, luv::vec2f pos);
  entt::entity enemyCreate(luv::AssetsManager* assetsManager,
      entt::registry& registry, luv::vec2f pos, entt::entity pId);

  entt::entity spellCreate(entt::registry& registry, luv::vec2f pos,
      int damage);

  entt::entity enemySpawnerCreate(entt::registry& registry, 
      luv::vec2f pos, float timeToSpawn, entt::entity playerId);
}
