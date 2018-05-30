cmake_minimum_required(VERSION 3.10)
project(roguelike)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-lncurses")

add_executable(roguelike main.cpp main.h)