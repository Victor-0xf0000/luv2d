#pragma once

#include <luv2d.hpp>

static const int STILE_WIDTH = 16;
static const int STILE_HEIGHT = 16;
static const int STILE_SCALE = 2;
static const int TILE_WIDTH = STILE_WIDTH * STILE_SCALE;
static const int TILE_HEIGHT = STILE_HEIGHT * STILE_SCALE;

struct Tile
{
  int ssx, ssy; // sprite sheet x, sprite sheet y
  int ix, iy; // index x, y
  bool air, collidable;
};

struct TileSet
{
private:
  Tile** layer1;
  Tile** layer2;
  int world_width, world_height;
  
  // TODO: Make ref
  luv::Texture* tilesheet;
public:
  TileSet();
  ~TileSet();
  
  void create(int world_width, int world_height, luv::Texture* tilesheet);
  void unload();

  void setTile(Tile* tile, int ix, int iy);
  Tile* getTile(int ix, int iy);
  Tile* getTile(int index);
  int getWidth() const;
  int getHeight() const;

  Tile** getLayer1();
  Tile** getLayer2();
  
  luv::vec2f indexToPos(int i);
  int posToIndex(luv::vec2f pos);

  luv::Texture* getTilesheet() const;
};
