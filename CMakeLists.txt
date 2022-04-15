cmake_minimum_required(VERSION 3.21)
project(Graphs)

set(CMAKE_CXX_STANDARD 20)

add_executable(Graphs main.cpp AdjMatrix.cpp AdjMatrix.h AdjList.cpp AdjList.h GraphInterface.h Utilities.cpp Utilities.h)
