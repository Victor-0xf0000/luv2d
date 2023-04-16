#pragma once

#include <room.hpp>
#include <luv2d.hpp>

#include <unordered_map>
#include <string>

struct Rooms
{
private:
  std::unordered_map<int, luv::Ref<Room>> rooms;
  
  luv::AssetsManager* assetsManagerPtr;

  int currentRoom;
  
  std::string roomsDir;
public:
  Rooms(luv::AssetsManager* assetsManager);
  ~Rooms();

  bool addRoom(int id, std::string path);
  bool addloadRoom(int id, std::string path);
  
  void setRoom(int id);
  void setRoomsDir(std::string path);
  
  // Set room to next room, if there's no next room, set to first room
  void nextRoom();
  
  // Set room to next room, if there's no next room, create one
  // Returns room id
  int nextOrCreate(int width, int height);

  // Set room to previous room, if there's no previous room, set to last room
  void previousRoom();

  void saveRoom(int id);
  void saveAllRooms();
  void saveCurrent();
  
  void loadRoom(int id);
  void unloadRoom(int id);

  luv::Ref<Room> getRoom(int id);
  luv::Ref<Room> getCurrentRoom();

  u32 currentId() const;
};
