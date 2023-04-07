#include <game.hpp>

int main(int argc, const char** argv)
{
  luv::Scope<Game> game = luv::createScope<Game>();
  game->init();

  return 0;
}
