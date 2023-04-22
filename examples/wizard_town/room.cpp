#include <room.hpp>
#include <entities.hpp>
#include <iostream>
#include <fstream>

Room::Room(int nid, luv::AssetsManager* assetsManager)
{
  this->tileset = luv::createRef<TileSet>();
  this->id = nid;
  this->path = "";
  this->assetsManagerPtr = assetsManager;
}

Room::~Room()
{
  this->unload();
}

template<typename C>
void savec(entt::registry& r, luv::Archive& arch, std::string label)
{
  arch << label << '\n';

  auto ccview = r.view<C>();
  u32 csize = ccview.size();
  arch << csize << '\n';

  for (auto [ent, c] : ccview.each())
  {
    u32 entid = static_cast<u32>(entt::to_entity(ent));
    arch << entid << ' ';
    c.save(arch);
    arch << '\n';
  }
  
  // Ending component section
  std::string line = "------------------";
  arch << line << '\n';
}

template<typename C>
void loadc(entt::registry& r, luv::Archive& arch)
{
  std::string trash;

  arch >> trash; // READING LABEL (TRASH)

  u32 csize;
  arch >> csize;
  
  for (u32 i = 0; i < csize; i++)
  {
    entt::entity ent;
    u32 entu;
    arch >> entu;
    ent = static_cast<entt::entity>(entu);

    C component;
    component.load(arch);
    r.emplace<C>(ent, component);
  }

  arch >> trash; // READING LABEL (TRASH)
}

template<typename C>
void loadassetsc(entt::registry& r, luv::AssetsManager* am, luv::Archive& arch)
{
  std::string trash;
  arch >> trash; // READING LABEL (TRASH)

  u32 csize;
  arch >> csize;

  for (u32 i = 0; i < csize; i++)
  {
    entt::entity ent;
    u32 entu;
    arch >> entu;
    ent = static_cast<entt::entity>(entu);

    C component;
    component.load(arch, am);
    r.emplace<C>(ent, component);
  }

  arch >> trash; // READING LABEL (TRASH)
}

// FILE STRUCT:
// tile-width (int)
// tile-height (int)
// tile0->air (int)
// ...
// tileN->air(int)
// Total entities (int)
// player id (int)
// amount entities using component T
// entity 0 using T
// entity 0 T serialization
// entity 1 using T
// entity 1 T serialization
// ...
// entity N using T
// entity N T serialization
// ...

void Room::createEmpty(int width, int height)
{
  this->playerId = entities::playerCreate(
      this->registry,
      this->assetsManagerPtr,
      {0.f, 0.f}
      );
  luv::Texture* tilesheet = this->assetsManagerPtr->getTexture("tilesheet");
  this->tileset->create(width, height, tilesheet);
}

bool Room::load()
{
  luv::Texture* tilesheet = this->assetsManagerPtr->getTexture("tilesheet");
  
  if (this->path == "assets/rooms/room0")
  {
    this->playerId = entities::playerCreate(
        this->registry,
        this->assetsManagerPtr,
        {70.f, 70.f}
        );
    this->tileset->create(64+1, 16+1, tilesheet);
    for (int i = 0; i < 64*16; i++)
    {
      luv::vec2f index = this->tileset->indexToPos(i);
      Tile* tile = this->tileset->getTile(i);
      tile->ix = index.x;
      tile->iy = index.y;
      tile->air = true;
    }
    for (int i = 0; i < 64-1; i++)
    {
      int index = this->tileset->posToIndex({i, 11.f});
      Tile* tile = this->tileset->getTile(index);
      tile->ssx = 0;
      tile->ssy = 0;
      tile->air = false;
      tile->collidable = true;
    }
    auto enemySpawner = entities::enemySpawnerCreate(
      this->registry,
      {0.f, 0.f},
      3.f,
      this->playerId
    );
  }
  else
  {
    luv::Archive arch(this->path.c_str(), std::ios_base::in);
    arch.load();
    int w, h;
    arch >> w;
    arch >> h;
    
    this->tileset->create(w, h, tilesheet);
    Tile** tiles = this->tileset->getLayer1();
    Tile** layer2 = this->tileset->getLayer2();
    for (int i = 0; i < w*h; i++)
    {
      int air, collidable, ssx, ssy;
      arch >> air;
      arch >> collidable;
      arch >> ssx;
      arch >> ssy;
      tiles[i]->air = air;
      tiles[i]->ssx = ssx;
      tiles[i]->ssy = ssy;
      tiles[i]->collidable = collidable;
      arch >> air;
      arch >> collidable;
      arch >> ssx;
      arch >> ssy;
      layer2[i]->air = air;
      layer2[i]->ssx = ssx;
      layer2[i]->ssy = ssy;
      layer2[i]->collidable = collidable;
    }

    u32 eSize;
    arch >> eSize;
  
    u32 playeridu;
    arch >> playeridu;
    this->playerId = static_cast<entt::entity>(playeridu);
    
    for (u32 _ = 0; _ < eSize; _++)
    {
      auto ent = this->registry.create();
    }
    
    loadc<Transform>(this->registry, arch);
    loadc<SquareSprite>(this->registry, arch);
    loadc<Control>(this->registry, arch);
    loadc<TileCollider>(this->registry, arch);
    loadc<Health>(this->registry, arch);
    loadc<Hitbox>(this->registry, arch);
    loadc<Mana>(this->registry, arch);
    loadc<Spell>(this->registry, arch);
    loadc<Enemy>(this->registry, arch);
    loadc<Follower>(this->registry, arch);
    loadc<EnemySpawner>(this->registry, arch);
    loadassetsc<AnimatedSprite>(this->registry, this->assetsManagerPtr, arch);
  }
  return true;
}

void Room::unload()
{
}

void Room::save()
{
  printf("Saving room: %i..\n", this->id);
  
  {
    luv::Archive arch(this->path.c_str(), std::ios_base::out);
    arch.load();
    arch.write("");
  }

  luv::Archive arch(this->path.c_str(), std::ios_base::app);
  arch.load();
  
  int tw = this->tileset->getWidth(), th = this->tileset->getHeight();

  arch << tw << '\n';
  arch << th << '\n';

  Tile** tiles = this->tileset->getLayer1();
  Tile** layer2 = this->tileset->getLayer2();
  for (int i = 0; i < this->tileset->getWidth()*this->tileset->getHeight(); i++)
  {
    int isair = (int) tiles[i]->air;
    int collidable = (int) tiles[i]->collidable;
    arch << isair << ' ' << collidable << ' ' << tiles[i]->ssx << ' ' << tiles[i]->ssy << '\n';
    isair = (int) layer2[i]->air;
    collidable = layer2[i]->collidable;
    arch << isair << ' ' << collidable << ' ' << layer2[i]->ssx << ' ' << layer2[i]->ssy << '\n';
  }
  u32 entitiesSize = this->registry.size();
  
  arch << entitiesSize << '\n';
  
  u32 pid = static_cast<u32>(entt::to_entity(this->playerId));

  arch << pid << '\n';


  savec<Transform>(this->registry, arch, "transform");
  savec<SquareSprite>(this->registry, arch, "square_sprite");
  savec<Control>(this->registry, arch, "control");
  savec<TileCollider>(this->registry, arch, "tile_collider");
  savec<Health>(this->registry, arch, "health");
  savec<Hitbox>(this->registry, arch, "hitbox");
  savec<Mana>(this->registry, arch, "mana");
  savec<Spell>(this->registry, arch, "spell");
  savec<Enemy>(this->registry, arch, "enemy");
  savec<Follower>(this->registry, arch, "follower");
  savec<EnemySpawner>(this->registry, arch, "enemy_spawner");
  savec<AnimatedSprite>(this->registry, arch, "animated_sprite");
  printf("Room %i saved.\n", this->id);
}

void Room::setPath(std::string npath)
{
  this->path = npath;
}

TileSet* Room::getTileSet()
{
  return this->tileset.get();
}

entt::registry& Room::getRegistry()
{
  return this->registry;
}

entt::entity& Room::getPlayerId()
{
  return this->playerId;
}
