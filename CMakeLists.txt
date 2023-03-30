cmake_minimum_required(VERSION 3.10)

project(luv2d)

string(TOLOWER ${CMAKE_SYSTEM_NAME} PLATFORM)

# Directory output files single config generators
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/luvSDK/lib 
  CACHE PATH "Output directory for static libraries.")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/luvSDK/lib
  CACHE PATH "Output directory for shared libraries.")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/luvSDK/bin
  CACHE PATH "Output directory for executables and DLL's.")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/luvSDK")
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(luv2d SHARED
  src/window.cpp
  src/engine.cpp
  src/application.cpp
  src/core/clock.cpp
  src/core/camera.cpp
  src/core/arena.cpp
  # graphics
  src/graphics/renderer.cpp
	src/graphics/texture.cpp
  src/graphics/renderable.cpp
	# events
  src/events/eventManager.cpp
  src/events/keyEvent.cpp
  src/events/applicationEvent.cpp
  src/events/mouseEvent.cpp
  # assets
  src/assets/assetsManager.cpp
  # thirdparty
  thirdparty/stb_image/stb_image_implementation.c
  )
target_include_directories(luv2d PUBLIC include)
target_include_directories(luv2d PUBLIC thirdparty)
target_compile_options(luv2d PUBLIC -Wall -O2)

if (PLATFORM STREQUAL "windows")
  target_compile_definitions(luv2d PRIVATE 
    LUV2D_ENGINE_IMPLEMENTATION LUV2D_PLATFORM_WINDOWS)
else ()
  target_compile_definitions(luv2d PRIVATE
    LUV2D_ENGINE_IMPLEMENTATION)
endif ()

# SDL2 LIBRARY

if (NOT EXISTS ${CMAKE_BINARY_DIR}/lib)
  file(COPY ${CMAKE_SOURCE_DIR}/dependencies/SDL2.lib DESTINATION ${CMAKE_BINARY_DIR}/lib)
  file(COPY ${CMAKE_SOURCE_DIR}/dependencies/SDL2main.lib DESTINATION ${CMAKE_BINARY_DIR}/lib)
endif ()
if (NOT EXISTS ${CMAKE_BINARY_DIR}/SDL2.dll)
  file(COPY ${CMAKE_SOURCE_DIR}/dependencies/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR}/luvSDK/bin)
endif ()

add_library(luvSDL2 STATIC IMPORTED)
set_target_properties(luvSDL2 PROPERTIES
  IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/lib/SDL2.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include/SDL2"
)

add_library(luvSDL2main STATIC IMPORTED)
set_target_properties(luvSDL2main PROPERTIES
  IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/lib/SDL2main.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include/SDL2"
)

target_link_libraries(luv2d PRIVATE mingw32 luvSDL2 luvSDL2main)

add_custom_command(TARGET luv2d POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}/include
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_PATH}/include/ ${OUTPUT_DIR}/include)

add_custom_command(TARGET luv2d POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}/bin/assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_PATH}/misc/data ${OUTPUT_DIR}/bin/assets)

#
# DEMO
#

project(demo)
add_executable(demo
  demo/main.cpp)
target_link_libraries(demo PRIVATE luv2d)
include_directories(demo PRIVATE include/)
