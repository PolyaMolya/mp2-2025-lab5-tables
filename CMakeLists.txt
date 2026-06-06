cmake_minimum_required(VERSION 3.10)
project(Polinoms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(test)

add_executable(tables
    src/main.cpp 
    src/polinoms.cpp
    src/SortedArrayTable.cpp
    src/HashTable.cpp
    src/AVLTreeTable.cpp
)