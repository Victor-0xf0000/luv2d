#include <tileset.hpp>
#include <luv2d.hpp>

TileSet::TileSet()
  : tiles(nullptr)
{
}

TileSet::~TileSet()
{
  delete[] this->tiles;
}

luv::vec2f TileSet::indexToPos(int i)
{
  int y = i / this->world_width;
  int x = i - (y*this->world_width);

  return {static_cast<float>(x), static_cast<float>(y)};
}

int TileSet::posToIndex(luv::vec2f pos)
{
  int x = static_cast<int>(pos.x);
  int y = static_cast<int>(pos.y);

  return y * this->world_width + x;
}

void TileSet::create(int width, int height)
{
  this->world_width = width;
  this->world_height = height;
  
  this->tiles = (Tile**) malloc(sizeof(Tile*)*world_width*world_height);
  for (int i = 0; i < world_width*world_height; i++)
  {
    Tile* t = new Tile();
    t->tex = nullptr;
    luv::vec2f pos = indexToPos(i);
    t->ix = static_cast<int>(pos.x);
    t->iy = static_cast<int>(pos.y);
    t->air = true;
    this->tiles[i] = t;
  }
}

void TileSet::setTile(Tile* tile, int ix, int iy)
{
  this->tiles[posToIndex({(float)ix, (float)iy})] = tile;
} 

Tile* TileSet::getTile(int ix, int iy)
{
  return this->tiles[posToIndex({(float)ix, (float)iy})];
}
Tile* TileSet::getTile(int index)
{
  return this->tiles[index];
}

Tile** TileSet::get()
{
  return this->tiles;
}
