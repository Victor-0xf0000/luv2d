#pragma once

#include <entt/entt.hpp>
#include <luv2d.hpp>
#include <tileset.hpp>
#include <algorithm>
#include <engine/graphics/renderer.hpp>
#include <cmath>
#include <entt/entt.hpp>
#include <entities.hpp>

namespace PhysicsSystem
{
  void update(const float& dt, entt::registry& registry); 
}

bool aabb(luv::Rect a, luv::Rect b);    
namespace TileCollisionSystem
{
  luv::Rect minkowskidiff(luv::Rect a, luv::Rect b);    

  float squared_distance(luv::vec2f a, luv::vec2f b);    

  luv::vec2f minkowskiCollide(luv::Rect a, luv::Rect b);    

  void update(const float& dt, TileSet* tileset, entt::registry& registry); 
}

namespace PlayerSystem
{
  void update(const float& dt, luv::Event& ev, luv::Camera* camera, entt::registry& registry); 

  void render(luv::Renderer* renderer, entt::registry& registry, entt::entity playerId); 
}

namespace HealthSystem
{
  void update(const float& dt, entt::registry& registry); 

  void render(entt::registry& registry, luv::Renderer* renderer); 
}

namespace SpellSystem
{
  void update(const float& dt, entt::registry& registry); 

  void render(luv::Renderer* renderer, entt::registry& registry); 
}

namespace FollowSystem
{
  void update(const float& dt, entt::registry& registry); 
}

namespace EnemySystem
{
  void update(const float& dt, luv::AssetsManager* assetsManager, 
      entt::registry& registry);; 
}

namespace SpriteSystem
{
  void update(const float& dt, entt::registry& registry);

  void render(luv::Renderer* renderer, entt::registry& registry);
}
