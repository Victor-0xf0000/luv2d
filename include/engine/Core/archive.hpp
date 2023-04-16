#pragma once

#include <engine/base.hpp>
#include <engine/platform.hpp>
#include <fstream>
#include <string>

namespace luv
{
  struct LUV2D_ENGINE_API Archive
  {
  private:
    luv::Ref<std::filebuf> fb;
    luv::Ref<std::ostream> os;
    luv::Ref<std::istream> is;
    std::string buffer;
    
    std::string path;
  
    std::ios::openmode mode;
  public:
    Archive(const char* path, std::ios::openmode mode);
    ~Archive();
    
    // Loads file's content into internal buffer
    bool load();

    // Unload buffers' data
    void unload();
    
    // Gets data if loaded
    std::string get();
    
    // Write data (erase the old data, then write the new)
    void write(std::string content);

    // Append data
    void append(std::string content);

    // Read file's data at the time
    static bool readFileToBuffer(std::string* buf, const char* path);
    
    luv::Archive& operator<<(std::string& str);
    luv::Archive& operator<<(char const& c);
    luv::Archive& operator<<(int& n);
    luv::Archive& operator<<(u32& n);
    luv::Archive& operator<<(float& f);

    luv::Archive& operator>>(std::string& str);
    luv::Archive& operator>>(char& c);
    luv::Archive& operator>>(int& n);
    luv::Archive& operator>>(u32& n);
    luv::Archive& operator>>(float& f);
  };
}
