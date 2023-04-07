#include <engine/graphics/font.hpp>

#include <engine/graphics/renderer.hpp>

#include <engine/base.hpp>

#include <stdio.h>

luv::Font::Font()
{
  
}

luv::Font::~Font()
{
  this->unload();
}

void luv::Font::render(SDL_Renderer* renderer, float x, float y, const char* text)
{
  u32 r, g, b, a;
  SDL_SetTextureColorMod(this->atlas, 255, 255, 255);
  SDL_SetTextureAlphaMod(this->atlas, 150);
  for (int i = 0; text[i]; i++)
  {
    if (text[i] >= 32 && text[i] < 128)
    {
      stbtt_packedchar* info = &this->chars[text[i] - 32];
      SDL_Rect src_rect = {info->x0, info->y0, 
        info->x1 - info->x0, 
        info->y1 - info->y0};
      SDL_Rect dst_rect = {x + info->xoff, y + info->yoff + this->size, 
        info->x1 - info->x0, 
        info->y1 - info->y0};
      SDL_RenderCopy(renderer, this->atlas, &src_rect, &dst_rect);
      x += info->xadvance;
    }
  }
}

void luv::Font::unload()
{
  if (this->atlas)
    SDL_DestroyTexture(this->atlas);
  if (this->info)
    free(this->info);
  if (this->chars)
    free(this->chars);
}

bool luv::Font::loadFromFile(SDL_Renderer* renderer, const char* path, int size)
{
  // TODO: Use your own file struct here
  SDL_RWops* rw = SDL_RWFromFile(path, "rb");
  if (!rw)
  {
    printf("Unable to load: %s\n", path);
    return false;
  }

  i64 fileSize = SDL_RWsize(rw);
  u8* buffer = (u8*) malloc(fileSize);
  if (SDL_RWread(rw, buffer, fileSize, 1) != 1) return false;
  SDL_RWclose(rw);

  this->info = (stbtt_fontinfo*) malloc(sizeof(stbtt_fontinfo));
  this->chars = (stbtt_packedchar*) malloc(sizeof(stbtt_packedchar)*96);
  this->size = (float)size; 
  if (stbtt_InitFont(this->info, buffer, 0) == 0)
  {
    free(buffer);
    this->unload();
    printf("Unable to initialize font: %s\n", path);
    return false;
  }

  // fill bitmap atlas with packed characters
  u8* bitmap = NULL;
  this->texture_size = 32;
  while (true)
  {
    bitmap = (u8*) malloc(this->texture_size*this->texture_size);
    stbtt_pack_context pack_context;
    stbtt_PackBegin(&pack_context, 
        bitmap, this->texture_size, this->texture_size, 0, 1, 0);
    stbtt_PackSetOversampling(&pack_context, 1, 1);
    if (!stbtt_PackFontRange(&pack_context, 
          buffer, 0, size, 32, 95, this->chars))
    {
      // too small
      free(bitmap);
      stbtt_PackEnd(&pack_context);
      this->texture_size *= 2;
    }
    else
    {
      stbtt_PackEnd(&pack_context);
      break;
    }
  }

  this->atlas = SDL_CreateTexture(renderer, 
      SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, 
      this->texture_size, this->texture_size);
  SDL_SetTextureBlendMode(this->atlas, SDL_BLENDMODE_BLEND);

  u32* pixels = (u32*) malloc(this->texture_size*this->texture_size*sizeof(u32));
  static SDL_PixelFormat* format = nullptr;
  if (format == nullptr) format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
  for (int i = 0; i < this->texture_size*this->texture_size; i++)
  {
    pixels[i] = SDL_MapRGBA(format, 0xff, 0xff, 0xff, bitmap[i]);
  }
  SDL_UpdateTexture(this->atlas, 
      NULL, pixels, this->texture_size*sizeof(u32));
  free(pixels);
  free(bitmap);

  // setup additional info
  this->scale = stbtt_ScaleForPixelHeight(this->info, size);
  stbtt_GetFontVMetrics(this->info, &this->ascent, 0, 0);
  this->baseline = (int) (this->ascent*this->scale);

  free(buffer);
  return true;
}

float luv::Font::measureText(const char* text)
{
  float width = 0.f;
  for (int i = 0; text[i]; i++)
  {
    if (text[i] >= 32 && text[i] < 128)
    {
      stbtt_packedchar* info = &this->chars[text[i]-32];
      width += info->xadvance;
    }
  }

  return width;
}
