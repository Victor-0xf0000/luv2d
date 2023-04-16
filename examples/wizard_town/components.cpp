#include <components.hpp>
#include <entities.hpp>
#include <stdio.h>

// spawnFunctionBinder { 0 };

bool SpawnFunctionBind::initialized { false };
luv::Ref<std::vector<SpawnFunction>> SpawnFunctionBind::bindings {  };

SpawnFunctionBind::SpawnFunctionBind()
{
  SpawnFunctionBind::initBind();
}

void SpawnFunctionBind::initBind()
{
  if (SpawnFunctionBind::initialized)
    return;

  SpawnFunctionBind::initialized = true;
  SpawnFunctionBind::bindings = luv::createRef<std::vector<SpawnFunction>>();
  
  SpawnFunctionBind::bindings.get()->push_back(entities::enemyCreate);
}

void savevec2f(luv::Archive& arch, const luv::vec2f& vec)
{
  float x = vec.x, y = vec.y;
  arch << x << ' ' << y << ' ';
}

void loadvec2f(luv::Archive& arch, luv::vec2f* vec)
{
  float x, y;
  arch >> x; 
  arch >> y;
  vec->x = x;
  vec->y = y;
}

void EnemySpawner::save(luv::Archive& archive)
{
  archive << timeLeftToSpawn << ' ';
  archive << spawnTime << ' ';
  u32 pid = static_cast<u32>(entt::to_entity(this->playerId));
  archive << pid << ' ';
  archive << spawnFunctionId << ' ';
}

void EnemySpawner::load(luv::Archive& archive)
{
  archive >> timeLeftToSpawn;
  archive >> spawnTime;
  u32 iplayerid;
  archive >> iplayerid;
  this->playerId= (entt::entity) iplayerid;
  archive >> spawnFunctionId;
  SpawnFunctionBind::initBind();
  this->spawnFunction = (*SpawnFunctionBind::bindings.get())[this->spawnFunctionId];
}
