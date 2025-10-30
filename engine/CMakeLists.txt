cmake_minimum_required(VERSION 3.30)
project(engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(engine
    src/window.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries(engine PUBLIC SDL3::SDL3)
