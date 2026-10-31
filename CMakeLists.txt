cmake_minimum_required(VERSION 3.15)
project(PingPong LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use an installed raylib if present, otherwise download and build it.
find_package(raylib 5.0 QUIET)
if(NOT raylib_FOUND)
    include(FetchContent)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(raylib)
endif()

add_executable(pingpong
    src/main.cpp
    src/Game.cpp
    src/Ball.cpp
    src/Paddle.cpp
)
target_include_directories(pingpong PRIVATE include)
target_link_libraries(pingpong PRIVATE raylib)

if(MSVC)
    target_compile_options(pingpong PRIVATE /W4)
else()
    target_compile_options(pingpong PRIVATE -Wall -Wextra)
endif()