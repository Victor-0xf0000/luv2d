cmake_minimum_required(VERSION 3.10)

project(luv2d)

include_directories(luv2d PUBLIC include)
include_directories(luv2d PUBLIC thirdparty)

add_executable(luv2d src/main.cpp
  src/window.cpp
  src/engine.cpp
  src/core/clock.cpp
  src/core/camera.cpp
  # graphics
  src/graphics/renderer.cpp
	src/graphics/texture.cpp
	# events
  src/events/eventManager.cpp
  src/events/keyEvent.cpp
  src/events/applicationEvent.cpp
  src/events/mouseEvent.cpp
  # thirdparty
  thirdparty/glad/glad.c
  thirdparty/stb_image/stb_image_implementation.c)
target_compile_options(luv2d PUBLIC -Wall -O2)

# SDL2 LIBRARY

if (NOT EXISTS ${CMAKE_BINARY_DIR}/lib)
  file(COPY ${CMAKE_SOURCE_DIR}/lib/SDL2.lib DESTINATION ${CMAKE_BINARY_DIR}/lib)
  file(COPY ${CMAKE_SOURCE_DIR}/lib/SDL2main.lib DESTINATION ${CMAKE_BINARY_DIR}/lib)
endif ()
if (NOT EXISTS ${CMAKE_BINARY_DIR}/SDL2.dll)
  file(COPY ${CMAKE_SOURCE_DIR}/lib/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR}/)
endif ()

add_library(luvSDL2 STATIC IMPORTED)
set_target_properties(luvSDL2 PROPERTIES
  IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/lib/SDL2.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/thirdparty/SDL2"
)

add_library(luvSDL2main STATIC IMPORTED)
set_target_properties(luvSDL2main PROPERTIES
  IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/lib/SDL2main.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/thirdparty/SDL2"
)

# linking

target_link_libraries(luv2d PUBLIC mingw32 opengl32 luvSDL2 luvSDL2main)

# Only ran in everytime cmake is modified or first time build, if bin/data doesn't exists, copy it form CMAKE_SOURCE_DIR/data
# if bin/data is deleted after building, it will not be replaced until you run cmake again
if (NOT EXISTS ${CMAKE_BINARY_DIR}/misc/data)
  file(COPY ${CMAKE_SOURCE_DIR}/misc/data DESTINATION ${CMAKE_BINARY_DIR})
endif ()

# ran everytime the projetct is built
#add_custom_target(copy-runtime-files ALL
#  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)
