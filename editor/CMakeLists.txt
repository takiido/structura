cmake_minimum_required(VERSION 3.30)
project(editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

add_executable(editor
    src/main.cpp
)


target_include_directories(editor
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(editor PRIVATE SDL3::SDL3 imgui engine)

target_link_directories(editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/include
)
