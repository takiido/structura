cmake_minimum_required(VERSION 3.27)
project(editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(editor src/main.cpp)

find_package(OpenGL REQUIRED)

target_link_libraries(editor
    PRIVATE
        SDL3::SDL3
        OpenGL::GL
        glfw
        imgui
)
