cmake_minimum_required(VERSION 3.10)

project(luv2d)

include_directories(luv2d PUBLIC include)

add_executable(luv2d src/main.cpp
  src/window.cpp
  src/engine.cpp
  # graphics
  src/graphics/renderer.cpp)
target_link_libraries(luv2d PUBLIC mingw32 SDL2main SDL2 SDL2_image)
