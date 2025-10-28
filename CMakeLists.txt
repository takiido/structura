cmake_minimum_required(VERSION 3.30)
project(structura LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (DEFINED ENV{IN_NIX_SHELL})
    message(STATUS"Nix environment detected...")
    find_package(SDL3)
else ()
    add_subdirectory(external/sdl3)
endif()

add_subdirectory(external/imgui)


add_subdirectory(engine)
add_subdirectory(editor)
