#include <tileset.hpp>
#include <luv2d.hpp>

TileSet::TileSet()
  : layer1(nullptr), layer2(nullptr)
{
}

TileSet::~TileSet()
{
  this->unload();
}

luv::vec2f TileSet::indexToPos(int i)
{
  int y = static_cast<int>(i / this->world_width);
  int x = i - (y*this->world_width);

  return {static_cast<float>(x), static_cast<float>(y)};
}

int TileSet::posToIndex(luv::vec2f pos)
{
  int x = static_cast<int>(pos.x);
  int y = static_cast<int>(pos.y);
 
  return y * this->world_width + x;
}

void TileSet::unload()
{
  for (int i = 0; i < world_width*world_height; i++)
  {
    delete this->layer1[i];
    delete this->layer2[i];
  }
  delete[] this->layer1;
  delete[] this->layer2;
}

void TileSet::create(int width, int height, luv::Texture* tilesheet)
{
  this->tilesheet = tilesheet;
  this->world_width = width;
  this->world_height = height;
  
  this->layer1 = (Tile**) malloc(sizeof(Tile*)*world_width*world_height);
  this->layer2 = (Tile**) malloc(sizeof(Tile*)*world_width*world_height);
  for (int i = 0; i < world_width*world_height; i++)
  {
    Tile* t = (Tile*) malloc(sizeof(Tile));
    luv::vec2f pos = indexToPos(i);
    t->ix = static_cast<int>(pos.x);
    t->iy = static_cast<int>(pos.y);
    t->ssx = -1;
    t->ssy = -1;
    t->air = true;
    t->collidable = false;
    this->layer1[i] = t;

    Tile* t2 = (Tile*) malloc(sizeof(Tile));
    t2->ix = static_cast<int>(pos.x);
    t2->iy = static_cast<int>(pos.y);
    t2->ssx = -1;
    t2->ssy = -1;
    t2->air = true;
    t2->collidable = false;
    this->layer2[i] = t2;
  }
}

void TileSet::setTile(Tile* tile, int ix, int iy)
{
  this->layer1[posToIndex({(float)ix, (float)iy})] = tile;
} 

Tile* TileSet::getTile(int ix, int iy)
{
  return this->layer1[posToIndex({(float)ix, (float)iy})];
}
Tile* TileSet::getTile(int index)
{
  return this->layer1[index];
}

int TileSet::getWidth() const
{
  return this->world_width;
}

int TileSet::getHeight() const
{
  return this->world_height;
}

Tile** TileSet::getLayer1()
{
  return this->layer1;
}

Tile** TileSet::getLayer2()
{
  return this->layer2;
}

luv::Texture* TileSet::getTilesheet() const
{
  return this->tilesheet;
}
