#pragma once

#ifdef LUV2D_PLATFORM_WINDOWS

#ifdef LUV2D_ENGINE_IMPLEMENTATION

#define LUV2D_ENGINE_API __declspec(dllexport)

#else

#define LUV2D_ENGINE_API __declspec(dllimport)

#endif // LUV2D_ENGINE_IMPLEMENTATION

#else

#define LUV2D_ENGINE_API

#endif // LUV2D_PLATFORM_WINDOWS
