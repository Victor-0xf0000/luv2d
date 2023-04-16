#pragma once

#include <luv2d.hpp>

static const int TILE_WIDTH = 32;
static const int TILE_HEIGHT = 32;

struct Tile
{
  int ix, iy; // index x, y
  bool air;
};

struct TileSet
{
private:
  Tile** tiles;
  int world_width, world_height;

public:
  TileSet();
  ~TileSet();
  
  void create(int world_width, int world_height);
  void unload();

  void setTile(Tile* tile, int ix, int iy);
  Tile* getTile(int ix, int iy);
  Tile* getTile(int index);
  int getWidth() const;
  int getHeight() const;

  Tile** get();
  
  luv::vec2f indexToPos(int i);
  int posToIndex(luv::vec2f pos);
};
