cmake_minimum_required(VERSION 2.8.11)
project(VirusGame)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

if (WIN32)
  find_package(SDL2 CONFIG REQUIRED)     # check if SDL2     is installed
  find_package(sdl2-gfx CONFIG REQUIRED) # check if SDL2_gfx is installed
  find_package(sdl2-ttf CONFIG REQUIRED) # check if SDL2_gfx is installed
endif (WIN32)
if (UNIX)
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
  find_package(SDL2 REQUIRED)     # check if SDL2     is installed
  find_package(SDL2_gfx REQUIRED) # check if SDL2_gfx is installed
  find_package(SDL2_ttf REQUIRED) # check if SDL2_gfx is installed
endif (UNIX)

include_directories(${SDL2_INCLUDE_DIRS})
find_path(SYSTEM_INCLUDE_DIR SDL2/SDL.h)
include_directories(${SYSTEM_INCLUDE_DIR})

add_executable(VirusGame VirusGame.cpp)

if (WIN32)
  target_link_libraries(VirusGame PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_gfx SDL@::SDL2_ttf)
endif (WIN32)
if (UNIX)
  target_link_libraries(VirusGame PRIVATE SDL2::Main SDL2::GFX SDL2::TTF)
endif (UNIX)
