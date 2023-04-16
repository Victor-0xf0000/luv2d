#pragma once

#include <luv2d.hpp>
#include <vector>
#include <entt/entt.hpp>

struct Transform
{
  luv::vec2f pos;
  int width, height;

  void save(luv::Archive& archive)
  {
    archive << pos.x << ' ' << pos.y << ' ';
    archive << width << ' ';
    archive << height << ' ';
  }
  
  void load(luv::Archive& archive)
  {
    archive >> pos.x;
    archive >> pos.y;
    archive >> width;
    archive >> height;
  }
};

template<typename T>
void savevector(luv::Archive& arch, const std::vector<T>& vec)
{
  u32 vecsize = vec.size();
  arch << vecsize << ' ';
  for (u32 i = 0; i < vec.size(); i++)
  {
    T vecelm = vec[i];
    arch << vecelm << ' ';
  }
}

void savevec2f(luv::Archive& arch, const luv::vec2f& vec);
void loadvec2f(luv::Archive& arch, luv::vec2f* vec);

template<typename T>
void loadvector(luv::Archive& arch, std::vector<T>* vec)
{
  u32 size;
  arch >> size;

  for (u32 i = 0; i < size; i++)
  {
    T elm;
    arch >> elm;
    vec->push_back(elm);
  }
}

struct AnimationInfo
{
  // Sprite sheet indexes
  std::vector<luv::vec2f> indexes;
  
  // Animation rate
  float fps;
};

struct AnimatedSprite
{
    std::vector<AnimationInfo> animations;
    i32 currentAnimation;
    i32 currentFrame;

    float time;

    // Size info for a single sprite
    luv::vec2f ssize;
    
    float scale;

    // Amount of sprites horizontaly and verticaly
    int swc, shc; // sprite width count, sprite height count
    
    // Texture that holds the spritesheet
    luv::Texture* spritesheet;
    std::string path;
    
    AnimatedSprite(){}

    AnimatedSprite(luv::Texture* texture, std::string path,
        std::vector<AnimationInfo> Animations, luv::vec2f ssize, float scale)
    {
      this->time = 0.f;
      this->currentFrame = 0;
      this->currentAnimation = 0;
      this->scale = scale;
      this->path = path;
      this->spritesheet = texture;
      this->animations = Animations;
      this->ssize = ssize;
    }

    void save(luv::Archive& archive)
    {
      // ---- SAVING ANIMATIONS ----
      u32 animationSize = this->animations.size();
      archive << animationSize << ' '; // ANIMATION SIZE
      for (u32 i = 0; i < animationSize; i++)
      {
        // ---- SAVING INDEXES ----
        u32 indexesSize = this->animations[i].indexes.size();
        archive << indexesSize << ' ';
        for (u32 j = 0; j < indexesSize; j++)
        {
          savevec2f(archive, this->animations[i].indexes[j]);
        }

        archive << this->animations[i].fps << ' ';
      }
      // ---- DONE SAVING ANIMATIONS ----
      archive << currentAnimation << ' ' << currentFrame << ' ';
      archive << time << ' ';
      savevec2f(archive, this->ssize);
      archive << scale << ' ';
      archive << path << ' ';
    }

    void load(luv::Archive& archive, luv::AssetsManager* am)
    {
      // ---- LOADING ANIMATIONS ----
      u32 animationSize;
      archive >> animationSize;
      for (u32 i = 0; i < animationSize; i++)
      {
        // ---- LOADING INDEXES ----
        u32 indexesSize;
        archive >> indexesSize;
        this->animations.push_back({std::vector<luv::vec2f>(), 0.f}); 
        for (u32 j = 0; j < indexesSize; j++)
        {
          luv::vec2f index;
          loadvec2f(archive, &index);
          this->animations[i].indexes.push_back(index);
        }
        
        archive >> this->animations[i].fps;
      }
      // ---- DONE LOADING ANIMATIONS ----
      archive >> currentAnimation;
      archive >> currentFrame;
      archive >> time;
      loadvec2f(archive, &this->ssize);
      archive >> scale;
      archive >> path;

      this->spritesheet = am->getTexture(this->path);
    }
};

struct SquareSprite
{
  luv::Color color;
  void save(luv::Archive& archive)
  {
    archive << color.r << ' ';
    archive << color.g << ' ';
    archive << color.b << ' ';
    archive << color.a << ' ';
  }
  
  void load(luv::Archive& archive)
  {
    archive >> color.r;
    archive >> color.g;
    archive >> color.b;
    archive >> color.a;
  }
};

struct Health
{
  int health;
  int maxHealth;
  
  int invincible;

  void damage(int damage)
  {
    this->health -= damage;
    if (this->health < 0)
      this->health = 0;
  }

  void cure(int cure)
  {
    this->health += cure;
    if (this->health > this->maxHealth)
      this->health = this->maxHealth;
  }
  
  void save(luv::Archive& archive)
  {
    archive << health << ' ';
    archive << maxHealth << ' ';
    archive << invincible << ' ';
  }
  
  void load(luv::Archive& archive)
  {
    archive >> health;
    archive >> maxHealth;
    archive >> invincible;
  }
};

struct Control
{
  luv::vec2f dir;
  
  void save(luv::Archive& archive)
  {
    archive << dir.x << ' ' << dir.y << ' ';
  }
  
  void load(luv::Archive& archive)
  {
    archive >> dir.x;
    archive >> dir.y;
  }
};

struct Enemy
{
  int damage;
  entt::entity playerId;
  float timeLeftToHit;
  float hitTime;

  void save(luv::Archive& archive)
  {
    archive << damage << ' ';
    u32 pid = static_cast<u32>(entt::to_entity(this->playerId));
    archive << pid << ' ';
    archive << timeLeftToHit << ' ';
    archive << hitTime << ' ';
  }
  
  void load(luv::Archive& archive)
  {
    archive >> damage;
    u32 iplayerid;
    archive >> iplayerid;
    this->playerId = (entt::entity) iplayerid;
    archive >> timeLeftToHit;
    archive >> hitTime;
  }
};

typedef entt::entity(*SpawnFunction)(luv::AssetsManager*, entt::registry&, luv::vec2f pos, entt::entity playerId);

//struct SpawnFunctionPair
//{
//  int id;
//  SpawnFunction func;
//};

struct SpawnFunctionBind final
{
  SpawnFunctionBind();

  static void initBind();
  
  static bool initialized;

  static luv::Ref<std::vector<SpawnFunction>> bindings;
};

static SpawnFunctionBind spawnFunctionBinder;

struct EnemySpawner
{
  float timeLeftToSpawn;
  float spawnTime;
  entt::entity playerId;
  SpawnFunction spawnFunction;
  int spawnFunctionId;

  void save(luv::Archive& archive);

  void load(luv::Archive& archive);
};

struct Spell
{
  int damage;
  float lifetime;
  float timeToHit;
  float timeLeftToHit;
  int startWidth, startHeight;

  void save(luv::Archive& archive)
  {
    archive << damage << ' ';
    archive << lifetime << ' ';
    archive << timeToHit << ' ';
    archive << timeLeftToHit << ' ';
    archive << startWidth << ' ' << startHeight << ' ';
  }
  
  void load(luv::Archive& archive)
  {
    archive >> damage;
    archive >> lifetime;
    archive >> timeToHit;
    archive >> timeLeftToHit;
    archive >> startWidth >> startHeight;
  }
};

struct Mana
{
  int mana;
  int maxMana;
  
  float manaRegenTime;
  float timeLeftToRegenMana;

  void loseMana(int qnt)
  {
    this->mana -= qnt;
    if (this->mana < 0)
      this->mana = 0;
  }

  void gainMana(int qnt)
  {
    this->mana += qnt;
    if (this->mana > this->maxMana)
      this->mana = this->maxMana;
  }

  void save(luv::Archive& archive)
  {
    archive << mana << ' ';
    archive << maxMana << ' ';
    archive << manaRegenTime << ' ';
    archive << timeLeftToRegenMana << ' ';
  }

  void load(luv::Archive& archive)
  {
    archive >> mana;
    archive >> maxMana;
    archive >> manaRegenTime;
    archive >> timeLeftToRegenMana;
  }
};

struct Follower
{
  entt::entity following;

  void save(luv::Archive& archive)
  {
    u32 pid = static_cast<u32>(entt::to_entity(this->following));
    archive << pid << ' ';
  }

  void load(luv::Archive& archive)
  {
    i32 ifollowing;
    archive >> ifollowing;
    this->following = (entt::entity) ifollowing;
  }
};

struct Hitbox
{
  luv::vec2f offset;
  int width, height;

  void save(luv::Archive& archive)
  {
    archive << offset.x << ' ' << offset.y << ' ';
    archive << width << ' ' << height << ' ';
  }

  void load(luv::Archive& archive)
  {
    archive >> offset.x >> offset.y;
    archive >> width >> height;
  }
};

struct TileCollider
{
  // Hitbox position and size
  luv::vec2f origin;
  int width, height;

  void save(luv::Archive& archive)
  {
    archive << origin.x << ' ' << origin.y << ' ';
    archive << width << ' ' << height << ' ';
  }

  void load(luv::Archive& archive)
  {
    archive >> origin.x >> origin.y;
    archive >> width >> height;
  }
};
