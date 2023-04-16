#include <game.hpp>
#include <entities.hpp>
#include <systems.hpp>

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>

void Game::onStart()
{
  printf("Just started!\n"); 

  this->AssetsManager()->loadTexture("player", "assets/player-sheet.png");
  this->rooms = luv::createRef<Rooms>(this->AssetsManager());
  this->rooms->setRoomsDir("assets/rooms/");

  this->Window()->change_title("Wizard town");
  this->arialf = this->AssetsManager()->loadFont("arial", "assets/arial.ttf", 24);
  this->tilling = false;
  this->erasing = false;
  

  this->uiSystem = luv::createRef<UiSystem>(this->arialf);

  int ww = this->Window()->get_width(), wh = this->Window()->get_height();

  this->Camera()->set_world_pos({ww/2, wh/2});
}

void Game::onTick()
{
  luv::Event e = this->EventManager()->getEvent();
  float dt = this->Clock()->getDeltaTime().get_seconds();
  
  this->uiSystem->inputUpdate(e);
  this->time = this->time + luv::Time::seconds(dt);

  if (this->time.get_milliseconds() > 700)
  {
    this->fps = static_cast<int>(1.f/dt);
    this->time = luv::Time::milliseconds(0);
  }

  if (e.containsType(luv::EventType::WindowClose))
    this->quit();
  
  int ww = this->Window()->get_width(), wh = this->Window()->get_height();

  if (this->uiSystem->uiButton(ww-100, 0, 100, 30, "Editor"))
  {
    if (this->tilling == true) 
      this->tilling = false;
    else
      this->tilling = true;
  }
  if (e.keyEvent.get_key(luv::KeyCode::RIGHT) == luv::KeyState::KEY_PRESSED)
    this->rooms->nextRoom();
  if (e.keyEvent.get_key(luv::KeyCode::LEFT) == luv::KeyState::KEY_PRESSED)
    this->rooms->previousRoom();

  luv::Ref<Room> currentRoom = this->rooms->getCurrentRoom();
  entt::registry& registry = currentRoom->getRegistry();
  TileSet* tileSet = currentRoom->getTileSet(); 
  
  if (!this->tilling)
  {
    const auto& cameraView = registry.view<Transform, Control>();
    for (auto [entity, tc, cc] : cameraView.each())
    {
      this->Camera()->set_world_pos({
          tc.pos.x+tc.width/2,
          tc.pos.y+tc.height/2});
    }
    PlayerSystem::update(dt, e, this->Camera(), registry);
    FollowSystem::update(dt, registry);
    PhysicsSystem::update(dt, registry);
    TileCollisionSystem::update(dt, tileSet, registry);
    EnemySystem::update(dt, this->AssetsManager(), registry);
    SpellSystem::update(dt, registry);
    HealthSystem::update(dt, registry);
    SpriteSystem::update(dt, registry);
  }
  else
  {
    this->uiSystem->beginMenu(ww-150, 40, 150, 300);
    if (this->uiSystem->uiButton(0, 0, 100, 30, "Save"))
      this->rooms->saveAllRooms();
    if (this->uiSystem->uiButton(0, 40, 100, 30, "New room"))
      this->rooms->nextOrCreate(32, 32);
    std::string roomid = "room: " + std::to_string(this->rooms->currentId());
    this->uiSystem->uiText(0, 80, roomid.c_str());
    this->uiSystem->endMenu();

    if (e.keyEvent.get_key(luv::KeyCode::W) == luv::KeyState::KEY_HOLD)
      this->Camera()->move_world_pos({0.f, -700.f*dt});
    if (e.keyEvent.get_key(luv::KeyCode::S) == luv::KeyState::KEY_HOLD)
      this->Camera()->move_world_pos({0.f, 700.f*dt});
    if (e.keyEvent.get_key(luv::KeyCode::A) == luv::KeyState::KEY_HOLD)
      this->Camera()->move_world_pos({-700.f*dt, 0.f});
    if (e.keyEvent.get_key(luv::KeyCode::D) == luv::KeyState::KEY_HOLD)
      this->Camera()->move_world_pos({700.f*dt, 0.f});
    if (e.keyEvent.get_key(luv::KeyCode::E) == luv::KeyState::KEY_PRESSED)
      this->erasing = !this->erasing;
    if (e.mouseEvent.get_button(luv::MouseButton::BUTTON_RIGHT) ==
        luv::MouseButtonState::MOUSE_BUTTON_HOLD)
    {
      float x = static_cast<float>(e.mouseEvent.mouse_x);
      float y = static_cast<float>(e.mouseEvent.mouse_y);
      luv::vec2f wpos = this->Camera()->convert_rect_to_world({
          x,
          y,
          1, 1
          }).pos;
      if (wpos.x > 0.f && wpos.x < TILE_WIDTH*tileSet->getWidth() &&
          wpos.y > 0.f && wpos.y < TILE_HEIGHT*tileSet->getHeight())
      {
        wpos = {
          static_cast<int>(static_cast<int>(wpos.x)/TILE_WIDTH), 
          static_cast<int>(static_cast<int>(wpos.y)/TILE_HEIGHT)};
        Tile* tile = tileSet->get()[tileSet->posToIndex(wpos)];
        if (this->erasing)
          tile->air = true;
        else
          tile->air = false;
      }
    }
  }
}

void Game::onRender()
{
  luv::Ref<Room> currentRoom = this->rooms->getCurrentRoom();
  entt::registry& registry = currentRoom->getRegistry();
  TileSet* tileSet = currentRoom->getTileSet(); 
 
  this->Renderer()->render_quad({
      0, 0,
      tileSet->getWidth()*TILE_WIDTH,
      tileSet->getHeight()*TILE_HEIGHT
      }, {90, 90, 90, 90});
  for (int i = 0; i < tileSet->getWidth()*tileSet->getHeight(); i++)
  {
    Tile* tile = tileSet->getTile(i);
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
  if (!this->tilling)
  {
    const auto view = registry.view<Transform, SquareSprite>().each();
    for (auto [entity, transf, spr] : view)
    {
      this->Renderer()->render_quad({
          transf.pos.x, transf.pos.y,
          transf.width,
          transf.height
          }, spr.color);
    }

    SpellSystem::render(this->Renderer(), registry);
    HealthSystem::render(registry, this->Renderer());
    PlayerSystem::render(this->Renderer(), registry, currentRoom->getPlayerId());
  } 
  
  SpriteSystem::render(this->Renderer(), registry);

  this->uiSystem->render(this->Renderer());
  this->Renderer()->setRenderViewMode(luv::RenderViewMode::RVM_SCREENVIEW);
  std::string fpsstr = "fps: " + std::to_string(this->fps);
  this->Renderer()->render_text(this->arialf.get(), 
      {500.f, 0.f}, fpsstr.c_str());
  this->Renderer()->setRenderViewMode(luv::RenderViewMode::RVM_CAMERAVIEW);
}

