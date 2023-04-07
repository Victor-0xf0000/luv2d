#pragma once

#include <entt/entt.hpp>
#include <luv2d.hpp>
#include <tileset.hpp>
#include <algorithm>

namespace PhysicsSystem
{
  static void update(const float& dt, entt::registry& registry)
  {

  }
}

namespace TileCollisionSystem
{
  bool aabb(luv::Rect a, luv::Rect b)
  {
    bool x = a.pos.x + a.width > b.pos.x && a.pos.x < b.pos.x + b.width;
    bool y = a.pos.y + b.height > b.pos.y && a.pos.y < b.pos.y + b.height;
    return x && y;
  }

  luv::Rect minkowskidiff(luv::Rect a, luv::Rect b)
  {
    luv::Rect ret;
    ret.width = a.width + b.width;
    ret.height = a.height + b.height;
    ret.pos.x = a.pos.x - b.pos.x - b.width;
    ret.pos.y = a.pos.y - b.pos.y - b.height;

    return ret;
  }

  float squared_distance(luv::vec2f a, luv::vec2f b)
  {
    return ((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y * b.y));
  }

  luv::vec2f minkowskiCollide(luv::Rect a, luv::Rect b)
  {
    luv::Rect minkowski = minkowskidiff(a, b);

    luv::vec2f min = {minkowski.pos.x, minkowski.pos.y};
    luv::vec2f max = {
      minkowski.pos.x+minkowski.width, 
      minkowski.pos.y+minkowski.height
    };

    if (0.f > minkowski.pos.x && 0.f < minkowski.pos.x+minkowski.width && 
        0.f > minkowski.pos.y && 0.f < minkowski.pos.y+minkowski.height)
    {
      luv::vec2f penetrationVec = {min.x, 0.f};
      float mindist = luv::absf(0.f-min.x);
      if (luv::absf(0.f-max.x) < mindist)
      {
        mindist = luv::absf(0.f-max.x);
        penetrationVec = {max.x, 0.f};
      }
      if (luv::absf(0.f-min.y) < mindist)
      {
        mindist = luv::absf(0.f-min.y);
        penetrationVec = {0.f, min.y-0.f};
      }
      if (luv::absf(0.f-max.y) < mindist)
      {
        mindist = luv::absf(0.f-max.y);
        penetrationVec = {0.f, max.y-0.f};
      }
      return penetrationVec;
    }
    return {0.f, 0.f};
  }

  static void update(const float& dt, TileSet* tileset, entt::registry& registry)
  {
    Tile** tiles = tileset->get();

    struct cdata {
      luv::vec2f pvec;
      luv::Rect tile;
      float sqrdist;
    };

    auto cmp = [](const cdata& data1, const cdata& data2){
      return data1.sqrdist > data2.sqrdist;
    };

    const auto colliderView = 
      registry.view<Transform, TileCollider>();
    for (auto [entity, t, tc] : colliderView.each())
    {
      std::vector<cdata> collisions;
      for (int i = 0; i < WORLD_TILE_WIDTH*WORLD_TILE_HEIGHT; i++)
      {
        if (tiles[i]->air) continue;
        luv::vec2f tilePos = tileset->indexToPos(i); 

        luv::vec2f pvec = minkowskiCollide({t.pos,t.width,t.height},{
            tilePos.x*TILE_WIDTH,
            tilePos.y*TILE_HEIGHT,
            TILE_WIDTH,
            TILE_HEIGHT
            });
        if (pvec.x != 0.f || pvec.y != 0.f)
        {
          collisions.push_back({pvec, {
                tilePos.x*TILE_WIDTH,
                tilePos.y*TILE_HEIGHT,
                TILE_WIDTH, TILE_HEIGHT
              }, 
              squared_distance(t.pos, 
                {tilePos.x*TILE_WIDTH, tilePos.y*TILE_HEIGHT})});
        }
      }
      std::sort(collisions.begin(), collisions.end(), cmp);
      for (auto data : collisions)
      {
        t.pos.x -= data.pvec.x;
        t.pos.y -= data.pvec.y;
      }
    }
  }
}

namespace PlayerSystem
{
  static void update(const float& dt, luv::Event& ev, entt::registry& registry)
  {
    const auto& controlView = registry.view<Transform, Control>();
    for (auto [entity, tc, cc] : controlView.each())
    {
      if (ev.keyEvent.get_key(luv::KeyCode::A) == luv::KeyState::KEY_HOLD)
      {
        tc.pos.x -= 300.f * dt;
      }
      if (ev.keyEvent.get_key(luv::KeyCode::D) == luv::KeyState::KEY_HOLD)
      {
        tc.pos.x += 300.f * dt;
      }
      if (ev.keyEvent.get_key(luv::KeyCode::W) == luv::KeyState::KEY_HOLD)
      {
        tc.pos.y -= 300.f * dt;
      }
      if (ev.keyEvent.get_key(luv::KeyCode::S) == luv::KeyState::KEY_HOLD)
      {
        tc.pos.y += 300.f * dt;
      }
    }
  }
}
