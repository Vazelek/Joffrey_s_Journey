cmake_minimum_required(VERSION 3.10)
project(game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)

file (GLOB_RECURSE sourceCode src/*.cpp src/*.h)

add_executable(game ${sourceCode})

target_link_libraries(game Qt5::Widgets Qt5::Multimedia)