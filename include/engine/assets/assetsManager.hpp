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
  struct Renderer;

  struct LUV2D_ENGINE_API TexturePath
  {
    std::string name;
    std::string path;
  };
  //struct AssetPair
  //{
  //  std::string name;
  //  luv::Asset asset;
  //};
  
  struct LUV2D_ENGINE_API TexturePair
  {
    std::string name;
    luv::Texture* texture;
  };

  struct LUV2D_ENGINE_API AssetsManager
  {
  private:
    std::unordered_map<std::string, luv::Ref<Texture>> textures; 
    luv::Ref<luv::Renderer> renderer_ptr;
  public:
    AssetsManager();
    ~AssetsManager();
    
    void create(luv::Ref<luv::Renderer> renderer);
    
    luv::Ref<luv::Texture> loadTexture(std::string name, std::string path);
    void loadTextures(std::vector<luv::TexturePath> paths);
    luv::Ref<luv::Texture> getTexture(std::string name);
    
    void unloadTexture(std::string name);
  };
}
