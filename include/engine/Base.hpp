#pragma once

#include <memory>
#include <cstdint>

#define BIT(x) (1 << x)
#define BIG_ENDIAN 0
#define LITTLE_ENDIAN 1

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

namespace luv
{
  template<typename T>
  using Scope = std::unique_ptr<T>;
  template<typename T, typename ... Args>
  constexpr Scope<T> createScope(Args&&... args)
  {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  template<typename T>
  using Ref = std::shared_ptr<T>;
  template<typename T, typename ... Args>
  constexpr Ref<T> createRef(Args&&... args)
  {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }

  constexpr int testByteOrder()
  {
    i16 word = 0x0001;
    i8* byte = (i8*) &word;
    return (byte[0] ? LITTLE_ENDIAN : BIG_ENDIAN);
  }
}
