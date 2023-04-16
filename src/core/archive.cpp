#include <engine/core/archive.hpp>

#include <iostream>
#include <fstream>

luv::Archive::Archive(const char* path, std::ios_base::openmode openmode)
{
  this->fb = luv::createRef<std::filebuf>();
  this->mode = openmode;
  this->path = path;
}

luv::Archive::~Archive()
{
  this->fb->close();
  this->unload();
}

// Loads file's content into internal buffer
bool luv::Archive::load()
{
  if (!this->fb->open(this->path, this->mode))
    return false;
  this->os = luv::createRef<std::ostream>(this->fb.get());
  this->is = luv::createRef<std::istream>(this->fb.get());
  luv::Archive::readFileToBuffer(&this->buffer, this->path.c_str());
  return true;
}

// Unload buffers' data
void luv::Archive::unload()
{
}

// Gets data if loaded
std::string luv::Archive::get()
{
  return this->buffer;
}

// Write data (erase the old data, then write the new)
void luv::Archive::write(std::string content)
{
  *this->os.get() << content;
}

// Append data
void luv::Archive::append(std::string content)
{
  *this->os.get() << content; 
} 

//
// WRITING
//

luv::Archive& luv::Archive::operator<<(std::string& str)
{ 
  *this->os.get() << str;  
  
  return *this;  
}  
  
luv::Archive& luv::Archive::operator<<(int& n)
{  
  *this->os.get() << n;  
  
  return *this;  
}  

luv::Archive& luv::Archive::operator<<(float& f)
{
  *this->os.get() << f;

  return *this;
}

luv::Archive& luv::Archive::operator<<(char const& c)
{
  *this->os.get() << c;

  return *this;
}

luv::Archive& luv::Archive::operator<<(u32& n)
{
  *this->os.get() << n;

  return *this;
}

//
// READING
//

luv::Archive& luv::Archive::operator>>(std::string& str)
{ 
  *this->is.get() >> str;  

  return *this; 
} 

luv::Archive& luv::Archive::operator>>(int& n)
{
  *this->is.get() >> n;

  return *this;
}

luv::Archive& luv::Archive::operator>>(float& f)
{
  *this->is.get() >> f;

  return *this;
}

luv::Archive& luv::Archive::operator>>(char& c)
{
  *this->is.get() >> c;

  return *this;
}

luv::Archive& luv::Archive::operator>>(u32& n)
{
  *this->is.get() >> n;

  return *this;
}

// Read file's data at the time 
bool luv::Archive::readFileToBuffer(std::string* buf, const char* path)
{ 
  std::filebuf sfb; 
  if (!sfb.open(path, std::ios::in))
  {
    std::cout << "Couldn't open: " << path << '\n';
    return false;
  }
  
  std::istream nis(&sfb);
  
  *buf = std::string(std::istreambuf_iterator<char>(nis), std::istreambuf_iterator<char>());

  sfb.close();
  return true;
}
