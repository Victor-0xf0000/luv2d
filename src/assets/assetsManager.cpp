#include <engine/assets/assetsManager.hpp>

#include <engine/graphics/renderer.hpp>
#include <engine/graphics/texture.hpp>

luv::AssetsManager::AssetsManager():renderer_ptr(nullptr)
{
  
}

luv::AssetsManager::~AssetsManager()
{
}

void luv::AssetsManager::create(luv::Ref<luv::Renderer> renderer)
{
  this->renderer_ptr = renderer;
}

luv::Ref<luv::Texture> luv::AssetsManager::loadTexture(std::string name, std::string path)
{
  luv::Ref<luv::Texture> texture = this->renderer_ptr->load_texture(path.c_str());
  this->textures[name] = texture;
  return texture;
}

void luv::AssetsManager::loadTextures(std::vector<luv::TexturePath> paths)
{
  for (auto path : paths)
  {
    this->loadTexture(path.name, path.path);
  }
}

luv::Texture* luv::AssetsManager::getTexture(std::string name)
{
  return this->textures.at(name).get();
}

void luv::AssetsManager::unloadTexture(std::string name)
{
  // this->textures->remove(name);
}
