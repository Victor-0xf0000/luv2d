#pragma once

#include <engine/core/arena.hpp>
#include <engine/platform.hpp>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//#define LUV_INVALID_HANDLE(T) (luv::Handle<T>{(int)0xFFFFFFFF, (int)0xFFFFFFFF})
//#define LUV_GET_SLOT_INDEX(slotInfo) ((int)((char*) (slotInfo) - slots.getData()) / sizeof(SlotInfo))
//
//namespace luv
//{
//  struct SlotInfo
//  {
//    union
//    {
//      int resourceIndex;
//      int nextFreeSlotIndex;
//    };
//    int version;
//  };
//
//  template<typename T>
//  struct LUV2D_ENGINE_API Handle
//  {
//  public:
//    int slotIndex;
//    int version;
//
//    inline int compare(const Handle<T>& other)
//    {
//      return this->slotIndex == other.slotIndex && this->version == other.version;
//    }
//
//    inline int operator==(const Handle<T>& other)
//    {
//      return this->compare(other);
//    }
//
//    inline int operator!=(const Handle<T>& other)
//    {
//      return !this->compare(other);
//    }
//  };
//
//  template<typename T>
//  struct LUV2D_ENGINE_API HandleList
//  {
//  private:
//    luv::Arena slots;
//    luv::Arena resources;
//
//    int resourceCount;
//    int freeSlotListCount;
//    int freeSlotListStart;
//    int typeSize;     
//  public:
//    HandleList(int initialCapacity)
//    {
//      this->slots.create(sizeof(SlotInfo) * initialCapacity);
//      this->resources.create(sizeof(T) * initialCapacity);
//      this->resourceCount = 0;
//      this->freeSlotListCount = 0;
//      this->freeSlotListStart = -1;
//      this->typeSize = sizeof(T);
//    }
//
//    ~HandleList() {}
//
//    luv::Handle<T> reserve()
//    {
//      SlotInfo* slotInfo;
//      this->resourceCount++;
//
//      if (this->freeSlotListCount)
//      {
//        // Reuse a free slot
//        this->freeSlotListCount--;
//        slotInfo = ((SlotInfo*) this->slots.getData()) + this->freeSlotListStart;
//        this->freeSlotListStart = slotInfo->nextFreeSlotIndex;
//      }
//      else
//      {
//        slotInfo = (SlotInfo*) this->slots.pushSize(sizeof(SlotInfo));
//        slotInfo->version = 0;
//        resources.pushSize(sizeof(T));
//      }
//      slotInfo->resourceIndex = this->resourceCount-1;
//
//      // Create a handle to the source
//      luv::Handle<T> handle;
//      handle.slotIndex = LUV_GET_SLOT_INDEX(slotInfo);
//      handle.version = slotInfo->version;
//      return handle;
//    }
//
//    luv::Handle<T> add(const T& t)
//    {
//      luv::Handle<T> handle = this->reserve();
//      T* resource = this->lookup(handle);
//      memcpy((void*) resource, (void*) &t, this->typeSize);
//      return handle;
//    }  
//  
//    void remove(luv::Handle<T> handle)
//    {
//      if (handle.slotIndex >= this->slots.getCapacity() / sizeof(T) || 
//          handle.slotIndex < 0)
//      {
//        printf("Attempting to remove a handle out of bounds\n");
//        return ;
//      }
//
//      SlotInfo* slotOfLast = ((SlotInfo*) this->slots.getData()) + this->resourceCount-1;
//      SlotInfo* slotOfRemoved = ((SlotInfo*) this->slots.getData()) + handle.slotIndex;
//      slotOfRemoved->version++;
//
//      if (slotOfRemoved != slotOfLast)
//      {
//        // Move the last resource to the space left by the removed resource
//        T* resourceLast = ((T*) this->resources.getData()) + slotOfLast->resourceIndex;
//        T* resourceRemoved = ((T*) this->resources.getData()) + slotOfRemoved->resourceIndex;
//        memcpy((void*) resourceRemoved, (void*) resourceLast,  this->typeSize);
//        slotOfLast->resourceIndex = slotOfRemoved->resourceIndex;
//      }
//      
//      slotOfRemoved->nextFreeSlotIndex = this->freeSlotListStart;
//      this->freeSlotListStart = handle.slotIndex;
//      this->freeSlotListCount++;
//      this->resourceCount--;
//    }
//    
//    T* lookup(luv::Handle<T> handle)
//    {
//      if (handle.slotIndex >= this->slots.getCapacity() / sizeof(SlotInfo) || handle.slotIndex < 0)
//      {
//        return nullptr;
//      }
//
//      SlotInfo* info = ((SlotInfo*) this->slots.getData()) + handle.slotIndex;
//      T* resource = nullptr;
//      if (handle.version == info->version)
//      {
//        resource = ((T*) this->resources.getData())+info->resourceIndex;
//      }
//      return resource;
//    }
//
//    void reset()
//    {
//      this->slots.reset();
//      this->resources.reset();
//      this->resourceCount = 0;
//      this->freeSlotListCount = 0;
//      this->freeSlotListStart = -1;
//    }
//
//    int count() const
//    {
//      return this->resourceCount;
//    }
//    
//    const T* getArray()
//    {
//      return (const T*) this->resources.getData();
//    }
//  };
//}
