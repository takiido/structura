cmake_minimum_required(VERSION 3.30)
project(engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(engine
    src/engine.cpp
)

target_link_libraries(engine PUBLIC SDL3::SDL3)
