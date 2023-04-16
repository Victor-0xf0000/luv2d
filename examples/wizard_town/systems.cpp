#include <systems.hpp>
#include <entities.hpp>
#include <components.hpp>
#include <luv2d.hpp>

void PhysicsSystem::update(const float& dt, entt::registry& registry)
{}

bool aabb(luv::Rect a, luv::Rect b)
{
  float aw = static_cast<float>(a.width);
  float ah = static_cast<float>(a.height);
  float bw = static_cast<float>(b.width);
  float bh = static_cast<float>(b.height);
  bool x = a.pos.x + aw > b.pos.x && a.pos.x < b.pos.x + bw;
  bool y = a.pos.y + ah > b.pos.y && a.pos.y < b.pos.y + bh;
  return x && y;
}
namespace TileCollisionSystem
{
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

  void update(const float& dt, TileSet* tileset, entt::registry& registry)
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
      for (int i = 0; i < tileset->getWidth()*tileset->getHeight(); i++)
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
  void update(const float& dt, luv::Event& ev, luv::Camera* camera, entt::registry& registry)
  {
    const auto& controlView = registry.view<Transform, Control, Health, Mana>();
    for (auto [entity, tc, cc, hc, mc] : controlView.each())
    {
      mc.timeLeftToRegenMana -= dt;
      if (mc.timeLeftToRegenMana <= 0.f)
      {
        mc.timeLeftToRegenMana = mc.manaRegenTime;
        mc.gainMana(15.f);
      }
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
      if (ev.keyEvent.get_key(luv::KeyCode::SPACE) == luv::KeyState::KEY_PRESSED)
      {
        hc.damage(7);
        if (hc.health == 0)
          hc.health = hc.maxHealth;
      }
      if (ev.mouseEvent.get_button(luv::MouseButton::BUTTON_LEFT) == 
          luv::MouseButtonState::MOUSE_BUTTON_PRESSED)
      {
        if (mc.mana >= 30.f)
        {
          float spell_x, spell_y;
          spell_x = static_cast<float>(ev.mouseEvent.mouse_x);
          spell_y = static_cast<float>(ev.mouseEvent.mouse_y);
          luv::Rect pos = camera->convert_rect_to_world({spell_x, spell_y, 1, 1});
          entities::spellCreate(registry, {pos.pos.x, pos.pos.y}, 5);
          mc.loseMana(30.f);
        }
      }
    }
  }

  void render(luv::Renderer* renderer, entt::registry& registry, entt::entity playerId)
  {
    if (!registry.valid(playerId))
      return;
    Mana& mana = registry.get<Mana>(playerId);
    renderer->setRenderViewMode(luv::RenderViewMode::RVM_SCREENVIEW);
    renderer->render_quad({
      0.f,
      0.f,
      28,
      100
    }, {70, 20, 30, 255});
    
    float scale = static_cast<float>(mana.mana) / static_cast<float>(mana.maxMana); 
    float height = 100.f*scale;
    
    renderer->render_quad({
      0.f,
      0.f,
      28,
      static_cast<int>(height)
    }, {70, 20, 130, 255});
    renderer->setRenderViewMode(luv::RenderViewMode::RVM_CAMERAVIEW);
  }
}

namespace HealthSystem
{
  void update(const float& dt, entt::registry& registry)
  {
    auto view = registry.view<Health>();
    for (auto [entity, hc] : view.each())
    {
      if (hc.health <= 0 && !hc.invincible)
        registry.destroy(entity);
    }
  }

  void render(entt::registry& registry, luv::Renderer* renderer)
  {
    auto view = registry.view<Transform, Health>();
    for (auto [entity, tc, hc] : view.each())
    {
      renderer->render_quad({
          tc.pos.x-30.f, tc.pos.y-25.f, 
          tc.width+60, 20},
          {70, 20, 30, 255});
      float scale = static_cast<float>(hc.health) / static_cast<float>(hc.maxHealth);
      float width = (static_cast<float>(tc.width) + 60.f) * scale;

      renderer->render_quad({
          tc.pos.x-30.f, tc.pos.y-25.f,
          static_cast<int>(width),20},
          {30, 70, 30, 255});
    }
  }
}

namespace SpellSystem
{
  void update(const float& dt, entt::registry& registry)
  {
    auto view = registry.view<Spell, Transform, Hitbox>();
    auto enemyView = registry.view<Transform, Hitbox, Health>();
    for (auto [entity, sc, tc, hc] : view.each())
    {
      sc.lifetime -= dt;
      sc.timeLeftToHit -= dt;
      
      float invltime = sc.lifetime;
      
      int nwidth = static_cast<int>(((float)sc.startWidth)*invltime);
      int nheight = static_cast<int>(((float)sc.startHeight)*invltime);

      tc.pos.x = tc.pos.x + hc.width/2.f - nwidth/2.f;
      tc.pos.y = tc.pos.y + hc.height/2.f - nheight/2.f;
      
      hc.width = nwidth;
      hc.height = nheight;

      
      tc.width = hc.width, tc.height = hc.height;
      if (sc.timeLeftToHit <= 0.f)
      {
        for (auto [enemy, etc, ehbc, ehc] : enemyView.each())
        {
          if (aabb({tc.pos, hc.width, hc.height}, 
                {etc.pos, ehbc.width, ehbc.height}))
          {
            ehc.damage(sc.damage);
            sc.timeLeftToHit = sc.timeToHit;
          }
        }
      } 
      if (sc.lifetime <= 0.f)
        registry.destroy(entity);
    }
  }

  void render(luv::Renderer* renderer, entt::registry& registry)
  {
    auto view = registry.view<Spell, Transform>();
    for (auto [entity, sc, tc] : view.each())
    {
      renderer->render_quad({
          tc.pos, tc.width, tc.height},
          {140, 30, 130, 255});
    }
  }
}

namespace FollowSystem
{
  void update(const float& dt, entt::registry& registry)
  {
    auto view = registry.view<Transform, Follower>();
    for (auto [entity, tc, fc] : view.each())
    {
      if (!registry.valid(fc.following))
        break;

      Transform ftc = registry.get<Transform>(fc.following);
      float angle = atan2(ftc.pos.y-tc.pos.y, ftc.pos.x-tc.pos.x);
      tc.pos.x += 150.f* dt * cos(angle);
      tc.pos.y += 150.f* dt * sin(angle);
    }
  }
}

namespace EnemySystem
{
  void update(const float& dt, luv::AssetsManager* assetsManager, 
      entt::registry& registry)
  {
    auto spawnView = registry.view<EnemySpawner, Transform>();
    for (auto [entity, spc, tc] : spawnView.each())
    {
      spc.timeLeftToSpawn -= dt;
      if (spc.timeLeftToSpawn <= 0.f)
      {
        spc.spawnFunction(assetsManager, registry, tc.pos, spc.playerId);
        spc.timeLeftToSpawn = spc.spawnTime;
      }
    }
  
    auto view = registry.view<Transform, Enemy, Hitbox>();
    for (auto [entity, tc, ec, hbc] : view.each())
    {
      // If player was destroyed
      if (!registry.valid(ec.playerId))
        break;
      Transform& ptc = registry.get<Transform>(ec.playerId);
      Hitbox& phbc = registry.get<Hitbox>(ec.playerId);
      Health& phc = registry.get<Health>(ec.playerId);
      
      ec.timeLeftToHit -= dt;
      
      if (ec.timeLeftToHit <= 0)
      {
        ec.timeLeftToHit = 0.f;
        if (aabb({tc.pos, hbc.width, hbc.height}, 
              {ptc.pos, phbc.width, phbc.height}))
        {
          phc.damage(ec.damage);
          ec.timeLeftToHit = ec.hitTime;
        }
      }  
    }
  }
}

namespace SpriteSystem
{
  void update(const float& dt, entt::registry& registry)
  {
    auto view = registry.view<AnimatedSprite>();
    for (auto [ent, asc] : view.each())
    {
      asc.time += dt;

      if (asc.time >= asc.animations[asc.currentAnimation].fps)
      {
        asc.currentFrame++;
        asc.time = 0.f;
        if (asc.currentFrame >= asc.animations[asc.currentAnimation].indexes.size())
          asc.currentFrame = 0;
      }
    }
  }

  void render(luv::Renderer* renderer, entt::registry& registry)
  {
    auto view = registry.view<Transform, AnimatedSprite>();
    for (auto [ent, tc, asc] : view.each())
    {
      luv::Rect src = {
        asc.animations[asc.currentAnimation].indexes[asc.currentFrame].x * asc.ssize.x,
        asc.animations[asc.currentAnimation].indexes[asc.currentFrame].y * asc.ssize.y,
        static_cast<int>(asc.ssize.x),
        static_cast<int>(asc.ssize.y)
      };
      renderer->render_texture(asc.spritesheet,
          src,
          {tc.pos, tc.width, tc.height});
    }
  }
}
