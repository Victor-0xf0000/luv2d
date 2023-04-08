#pragma once

#include <luv2d.hpp>
#include <entt/entt.hpp>

struct Transform
{
  luv::vec2f pos;
  int width, height;
};

struct SquareSprite
{
  luv::Color color;
};

struct RigidBody
{
  luv::vec2f acc;
};

struct Health
{
  int health;
  int maxHealth;

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
};

struct Control
{
  luv::vec2f dir;
};

struct Enemy
{
  int damage;
  entt::entity playerId;
  float timeLeftToHit;
  float hitTime;
};

struct EnemySpawner
{
  float timeLeftToSpawn;
  float spawnTime;
  entt::entity playerId;

  entt::entity(*spawnFunction)(luv::AssetsManager* assetsManager, 
      entt::registry& registry, luv::vec2f pos, entt::entity playerId);
};

struct Spell
{
  int damage;
  float lifetime;
  float timeToHit;
  float timeLeftToHit;
  int startWidth, startHeight;
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
};

struct Follower
{
  entt::entity following;
};

struct Hitbox
{
  luv::vec2f offset;
  int width, height;
};

struct TileCollider
{
  // Hitbox position and size
  luv::vec2f origin;
  int width, height;
};
