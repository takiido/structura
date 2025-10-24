cmake_minimum_required(VERSION 3.30)
project(editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(editor src/main.cpp)

find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED)

if (NOT DEFINED ENV{IN_NIX_SHELL})
    file(GLOB IMGUI_SOURCES
        ${CMAKE_SOURCE_DIR}/external/imgui/*.cpp
        ${CMAKE_SOURCE_DIR}/external/imgui/*.h
        ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_sdl3.cpp
        ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
    )

    add_library(imgui STATIC ${IMGUI_SOURCES})

    target_include_directories(imgui PUBLIC 
        ${CMAKE_SOURCE_DIR}/external/imgui
        ${CMAKE_SOURCE_DIR}/external/imgui/backends
    )
endif()

target_link_libraries(editor
    PUBLIC
        SDL3::SDL3
        OpenGL::GL
        imgui
)
