cmake_minimum_required(VERSION 3.27)
project(structura LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED CONFIG)
find_package(SDL3 REQUIRED CONFIG)
find_package(imgui REQUIRED CONFIG)

add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(runtime)
