#include <engine/core/arena.hpp>
#include <stdio.h>

luv::Arena::Arena():
  data(nullptr), capacity(0), used(0)
{
  
}

luv::Arena::~Arena()
{
  free(this->data);
}

void luv::Arena::create(size_t inital_size)
{
  this->capacity = inital_size;
  data = (char*) malloc(this->capacity);
}

char* luv::Arena::pushSize(size_t size)
{
  // If the capacity can't handle anymore, double it
  if (this->used + size >= this->capacity)
  {
    size_t newCapacity = 2 * (this->capacity + size);
    // get next pow2 larger than current capacity
    newCapacity = (newCapacity >> 1) | newCapacity;
    newCapacity = (newCapacity >> 2) | newCapacity;
    newCapacity = (newCapacity >> 4) | newCapacity;
    newCapacity = (newCapacity >> 8) | newCapacity;
    newCapacity = (newCapacity >> 16) | newCapacity;
    newCapacity = (newCapacity >> 32) | newCapacity;
    newCapacity++;
    this->data = (char*) realloc(this->data, newCapacity);
    this->capacity = newCapacity;
  }

  char* memPtr = this->data + used;
  this->used += size;
  return memPtr;
}

inline void luv::Arena::reset()
{
  this->used = 0;
}

size_t luv::Arena::getCapacity()
{
  return this->capacity;
}

size_t luv::Arena::getUsed()
{
  return this->used;
}

char* luv::Arena::getData() const
{
  return this->data;
}
