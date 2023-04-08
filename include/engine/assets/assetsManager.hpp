#pragma once

#include <engine/base.hpp>
#include <engine/platform.hpp>
#include <engine/core/handlelist.hpp>

#include <unordered_map>
#include <vector>
#include <string>

namespace luv
{
  struct Texture;
  struct Font;
  struct Renderer;

  struct LUV2D_ENGINE_API TexturePath
  {
    std::string name;
    std::string path;
  };

  struct LUV2D_ENGINE_API FontPath
  {
    std::string name;
    std::string path;
    int size;
  };
  
  struct LUV2D_ENGINE_API TexturePair
  {
    std::string name;
    luv::Texture* texture;
  };
  
  struct LUV2D_ENGINE_API FontPair
  {
    std::string name;
    luv::Font* font;
  };

  struct LUV2D_ENGINE_API AssetsManager
  {
  private:
    std::unordered_map<std::string, luv::Ref<Texture>> textures; 
    std::unordered_map<std::string, luv::Ref<Font>> fonts; 
    luv::Ref<luv::Renderer> renderer_ptr;
  public:
    AssetsManager();
    ~AssetsManager();
    
    void create(luv::Ref<luv::Renderer> renderer);
    
    luv::Ref<luv::Texture> loadTexture(std::string name, std::string path);
    void loadTextures(std::vector<luv::TexturePath> paths);
    luv::Texture* getTexture(std::string name);
    void unloadTexture(std::string name);

    luv::Ref<luv::Font> loadFont(std::string name, std::string path, int size);
    void loadFonts(std::vector<luv::FontPath> paths);
    luv::Font* getFont(std::string name);
    void unloadFont(std::string name);
  };
}
