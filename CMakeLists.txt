cmake_minimum_required(VERSION 3.10)

project(luv2d)

include_directories(luv2d PUBLIC include)

add_executable(luv2d src/main.cpp
  src/window.cpp
  src/engine.cpp
  src/core/clock.cpp
  # graphics
  src/graphics/renderer.cpp
	src/graphics/texture.cpp
	# events
  src/events/eventManager.cpp
  src/events/keyEvent.cpp
  src/events/applicationEvent.cpp
  src/events/mouseEvent.cpp)
target_link_libraries(luv2d PUBLIC mingw32 SDL2main SDL2 SDL2_image)

# Only ran in everytime cmake is modified or first time build, if bin/data doesn't exists, copy it form CMAKE_SOURCE_DIR/data
# if bin/data is deleted after building, it will not be replaced until you run cmake again
if (NOT EXISTS ${CMAKE_BINARY_DIR}/data)
  file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
endif ()

# ran everytime the projetct is built
#add_custom_target(copy-runtime-files ALL
#  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)
