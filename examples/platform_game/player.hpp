#pragma once

#include <entt/entt.hpp>
#include <components.hpp>
#include <luv2d.hpp>

namespace entities
{
  entt::entity playerCreate(luv::AssetsManager* assetsManager, 
      entt::registry& registry, luv::vec2f pos)
  {
    auto player = registry.create();
    registry.emplace<Transform>(player, pos, 40, 60);
    registry.emplace<SquareSprite>(player);
    registry.emplace<Control>(player, 0.f, 0.f);
    registry.emplace<TileCollider>(player, 0.f, 0.f, 40, 60);
    registry.emplace<Health>(player, 100, 100);
    registry.emplace<Hitbox>(player, 0.f, 0.f, 40, 60);
    registry.emplace<Mana>(player, 300, 300, 0.2f, 0.2f);
    registry.get<SquareSprite>(player).color = 
      luv::Color(50, 60, 80, 255);

    return player;
  }   
  entt::entity enemyCreate(luv::AssetsManager* assetsManager,
      entt::registry& registry, luv::vec2f pos, entt::entity pId)
  {
    auto enemy = registry.create();
    registry.emplace<Transform>(enemy, pos, 40, 40);
    registry.emplace<SquareSprite>(enemy, luv::Color(90, 20, 30, 255));
    registry.emplace<TileCollider>(enemy, 0.f, 0.f, 40, 40);
    registry.emplace<Health>(enemy, 30, 30);
    registry.emplace<Hitbox>(enemy, 0.f, 0.f, 40, 40);
    registry.emplace<Enemy>(enemy, 20, pId, 0.5f, 0.5f);
    registry.emplace<Follower>(enemy, pId);
    return enemy;
  }

  entt::entity spellCreate(entt::registry& registry, luv::vec2f pos, int damage)
  {
    auto spell = registry.create();
    
    const float lifetime = 3.f;
    const int size = 60/lifetime;
    const float timeToHit = 0.5f;

    //luv::vec2f npos = {
    //  pos.x - static_cast<float>(size)*3.f/2.f,
    //  pos.y - static_cast<float>(size)*3.f/2.f
    //};
    luv::vec2f npos = {
      pos.x - size/2.f , 
      pos.y - size/2.f 
    };
    registry.emplace<Transform>(spell, npos, size, size);
    registry.emplace<Spell>(spell, damage, lifetime, 
        timeToHit, timeToHit, size, size);
    registry.emplace<Hitbox>(spell, 0.f, 0.f, size, size);
    return spell;
  }

  entt::entity enemySpawnerCreate(entt::registry& registry, 
      luv::vec2f pos, float timeToSpawn, entt::entity playerId)
  {
    auto spawner = registry.create();
    registry.emplace<Transform>(spawner, pos, 1, 1);
    registry.emplace<EnemySpawner>(spawner, 
        timeToSpawn, timeToSpawn, playerId, enemyCreate);
    return spawner;
  }
}
