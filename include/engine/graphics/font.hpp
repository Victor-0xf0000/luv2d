#pragma once

#include <engine/platform.hpp>

#include <SDL2/SDL.h>
#include <stb_truetype/stb_truetype.h>

// NOTE: Implementation of font depends on the rendering api
// It can be different if used opengl, directx, SDL2 etc
// For now We only use SDL2

namespace luv
{
  struct Renderer;
  struct LUV2D_ENGINE_API Font
  {
    friend Renderer;
  private:
    stbtt_fontinfo* info;
    stbtt_packedchar* chars;
    // TODO: Use your own texture struct here
    SDL_Texture* atlas;
    int texture_size;
    float size;
    float scale;
    int ascent;
    int baseline;
    
    // Meant to be called by the renderer itself
    void render(SDL_Renderer* renderer, float x, float y, const char* text);
  public:
    Font();
    ~Font();
    
    bool loadFromFile(SDL_Renderer* renderer, const char* path, int size);
    void unload();

    float measureText(const char* text);
  };
}
