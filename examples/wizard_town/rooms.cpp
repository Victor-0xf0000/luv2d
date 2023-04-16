#include <rooms.hpp>
#include <room.hpp>

Rooms::Rooms(luv::AssetsManager* assetsManager)
{
  this->assetsManagerPtr = assetsManager;
  this->roomsDir = "rooms/";
}

Rooms::~Rooms()
{
}

bool Rooms::addRoom(int id, std::string path)
{
  luv::Ref<Room> room = luv::createRef<Room>(id, this->assetsManagerPtr);
  room->setPath(path);
  this->rooms.insert({id, room});
  return true;
}

bool Rooms::addloadRoom(int id, std::string path)
{
  this->addRoom(id, path);
  return this->rooms.at(id)->load();
}

void Rooms::saveRoom(int id)
{
  this->rooms.at(id)->save();
}

void Rooms::saveCurrent()
{
  this->rooms.at(this->currentRoom)->save();
}

void Rooms::setRoom(int id)
{
  this->currentRoom = id;
}

void Rooms::setRoomsDir(std::string path)
{
  this->roomsDir = path;
  
  // Get rooms
  std::string roomPath = this->roomsDir + "rooms";
  luv::Archive arch(roomPath.c_str(), std::ios_base::in);
  arch.load();
  
  u32 roomsCount;
  arch >> roomsCount;
  
  u32 startingRoom;
  arch >> startingRoom;
  
  for (u32 i = 0; i < roomsCount; i++)
  {
    u32 roomid;
    arch >> roomid;

    std::string path;
    arch >> path;
 
    this->addloadRoom(roomid, std::string(this->roomsDir+path));
  }

  this->setRoom(startingRoom);
}

// Set room to next room, if there's no next room, set to first room
void Rooms::nextRoom()
{
  // If there's no next room, set current room to 0
  if (this->currentRoom + 1 >= this->rooms.size())
  {
    this->currentRoom = 0;
    this->setRoom(this->currentRoom);
    
    return ;
  }
  
  this->currentRoom++;
  this->setRoom(this->currentRoom);
}

// Set room to next room, if there's no next room, create one
int Rooms::nextOrCreate(int width, int height)
{
  if (this->currentRoom + 1 >= this->rooms.size())
  {
    this->currentRoom++;
    this->addRoom(this->currentRoom, 
        this->roomsDir + "room" + std::to_string(this->currentRoom));

    this->getCurrentRoom()->createEmpty(width, height);
    
    return this->currentRoom; // New room id
  }
  else
  {
    this->nextRoom();
    return this->currentRoom;
  }
}

// Set room to previous room, if there's no previous room, set to last room
void Rooms::previousRoom()
{
  // If there's no previous room, set current room to last one
  if (this->currentRoom - 1 < 0)
  {
    this->currentRoom = this->rooms.size() - 1;
    this->setRoom(this->currentRoom);

    return ;
  }
  this->currentRoom--;
  this->setRoom(this->currentRoom);
}

void Rooms::saveAllRooms()
{
  std::string roomsDataPath = this->roomsDir + "rooms";
  luv::Archive roomsData(roomsDataPath.c_str(), std::ios_base::out);
  roomsData.load();
  
  u32 totalRooms = this->rooms.size();
  
  roomsData << totalRooms << '\n';
  roomsData << this->currentRoom << '\n';
  
  for (auto room : this->rooms)
  {
    std::string roomPath = "room" + std::to_string(room.first);
    
    u32 roomid = room.first;

    roomsData << roomid << '\n';
    roomsData << roomPath << '\n';

    room.second->save();
  }
}

void Rooms::loadRoom(int id)
{
  this->rooms.at(id)->load();
}

void Rooms::unloadRoom(int id)
{
  this->rooms.at(id)->unload();
}

luv::Ref<Room> Rooms::getRoom(int id)
{
  return this->rooms.at(id);
}

luv::Ref<Room> Rooms::getCurrentRoom()
{
  return this->rooms.at(this->currentRoom);
}

u32 Rooms::currentId() const
{
  return this->currentRoom;
}
