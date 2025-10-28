cmake_minimum_required(VERSION 3.30)
project(editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

add_executable(editor
    src/main.cpp
    src/test.cpp
)


target_include_directories(editor
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(editor PUBLIC SDL3::SDL3 imgui)
