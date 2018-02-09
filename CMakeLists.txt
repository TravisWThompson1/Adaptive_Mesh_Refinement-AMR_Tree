cmake_minimum_required(VERSION 3.8)
project(Adaptive_Mesh_Refinement)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/AMR_Tree.cpp include/AMR_Tree.h src/Node.cpp include/Node.h include/Control.h src/Point.cpp include/Point.h src/Static_Mesh_Tree.cpp include/Static_Mesh_Tree.h)

add_executable(Adaptive_Mesh_Refinement ${SOURCE_FILES})