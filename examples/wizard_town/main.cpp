#include <game.hpp>
#include <luv2d.hpp>
#include <iostream>
#include <vector>

int main(int argc, const char** argv)
{
  luv::Ref<Game> game = luv::createRef<Game>();
  game->init();
  
  return 0;
}
