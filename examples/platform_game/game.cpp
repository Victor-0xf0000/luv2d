#include <game.hpp>
#include <player.hpp>
#include <systems.hpp>

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>

void Game::onStart()
{
  printf("Just started!\n"); 
  
  this->arialf = this->AssetsManager()->loadFont("arial", "assets/arial.ttf", 24);

  this->playerId = entities::playerCreate(
      this->AssetsManager(),
      this->registry,
      {70.f, 70.f});
  auto enemySpawner = entities::enemySpawnerCreate(
      this->registry,
      {300.f, 90.f},
      2.f,
      this->playerId
  );

  int ww = this->Window()->get_width(), wh = this->Window()->get_height();

  this->Camera()->set_world_pos({ww/2, wh/2});
  
  this->tileset = luv::createRef<TileSet>();
  this->tileset->create(WORLD_TILE_WIDTH, WORLD_TILE_HEIGHT);
  
  for (int i = 0; i < WORLD_TILE_WIDTH*WORLD_TILE_HEIGHT; i++)
  {
    luv::vec2f index = this->tileset->indexToPos(i);
    Tile* tile = this->tileset->getTile(i);
    tile->tex = nullptr;
    tile->ix = index.x;
    tile->iy = index.y;
    tile->air = (TILES[i]==1 ? false : true);
  }
}

void Game::onTick()
{
  luv::Event e = this->EventManager()->getEvent();
  float dt = this->Clock()->getDeltaTime().get_seconds();

  this->time = this->time + luv::Time::seconds(dt);

  if (this->time.get_milliseconds() > 700)
  {
    printf("FPS: %f\n", 1.f/dt);
    this->time = luv::Time::milliseconds(0);
  }

  if (e.containsType(luv::EventType::WindowClose))
    this->quit();
  
  const auto& cameraView = this->registry.view<Transform, Control>();
  for (auto [entity, tc, cc] : cameraView.each())
  {
    this->Camera()->set_world_pos({
        tc.pos.x+tc.width/2,
        tc.pos.y+tc.height/2});
  }

  PlayerSystem::update(dt, e, this->Camera(), this->registry);
  FollowSystem::update(dt, this->registry);
  PhysicsSystem::update(dt, this->registry);
  TileCollisionSystem::update(dt, this->tileset.get(), this->registry);
  EnemySystem::update(dt, this->AssetsManager(), this->registry);
  SpellSystem::update(dt, this->registry);
  HealthSystem::update(dt, this->registry);
}

void Game::onRender()
{
  this->Renderer()->render_quad({
      0, 0,
      WORLD_TILE_WIDTH*TILE_WIDTH,
      WORLD_TILE_HEIGHT*TILE_HEIGHT
      }, {90, 90, 90, 90});
  for (int i = 0; i < WORLD_TILE_WIDTH*WORLD_TILE_HEIGHT; i++)
  {
    Tile* tile = this->tileset->getTile(i);
    if (tile->air == false)
    {
      this->Renderer()->render_quad({
          tile->ix*TILE_WIDTH,
          tile->iy*TILE_HEIGHT,
          TILE_WIDTH,
          TILE_HEIGHT
          }, {90, 20, 20, 255});
    }
  }

  const auto view = this->registry.view<Transform, SquareSprite>().each();
  for (auto [entity, transf, spr] : view)
  {
    //this->Renderer()->render_texture(spr.texture,{
    //    transf.pos.x, transf.pos.y,
    //    transf.width,
    //    transf.height
    //});
    this->Renderer()->render_quad({
        transf.pos.x, transf.pos.y,
        transf.width,
        transf.height
    }, spr.color);
  }
  this->Renderer()->setRenderViewMode(luv::RenderViewMode::RVM_SCREENVIEW);
  this->Renderer()->render_quad_text(this->arialf.get(),
  {
      150.f,
      150.f,
      100,
      60
  }, {150, 150, 150, 50},
  "I am not a button",
  {150, 100, 100, 255});

  this->Renderer()->setRenderViewMode(luv::RenderViewMode::RVM_CAMERAVIEW);
  SpellSystem::render(this->Renderer(), this->registry);
  HealthSystem::render(this->registry, this->Renderer());
  PlayerSystem::render(this->Renderer(), this->registry, this->playerId);
}




