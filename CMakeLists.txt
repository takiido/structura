cmake_minimum_required(VERSION 3.27)
project(structura LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (DEFINED ENV{IN_NIX_SHELL})
    message(STATUS "Using system SDL3 from Nix environment")
    find_package(SDL3 REQUIRED CONFIG)
else()
    message(STATUS "Using external SDL3 submodule")
    add_subdirectory(external/sdl3)
endif()


add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(runtime)
