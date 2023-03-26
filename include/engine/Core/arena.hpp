#pragma once

#include <stdlib.h>

namespace luv
{
  struct Arena
  {
  private:
    char* data;
    size_t capacity;
    size_t used;
  public:
    Arena();
    ~Arena();
    
    void create(size_t inital_size);
    
    char* pushSize(size_t size);
    inline void reset();

    size_t getCapacity();
    size_t getUsed();
    char* getData() const;
  };
}
