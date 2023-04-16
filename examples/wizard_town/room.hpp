#pragma once

#include <tileset.hpp>
#include <luv2d.hpp>
#include <entt/entt.hpp>
#include <string>

struct Room
{
private:
  luv::Ref<TileSet> tileset;
  luv::AssetsManager* assetsManagerPtr;
  entt::registry registry;
  entt::entity playerId;

  std::string path;
  int id;
public:
  Room(int nid, luv::AssetsManager* assetsManager);
  ~Room();

  bool load();
  void unload();
  
  void createEmpty(int width, int height);
  
  void save();
  
  void setPath(std::string npath);
  
  TileSet* getTileSet();
  entt::registry& getRegistry();
  entt::entity& getPlayerId();
};
