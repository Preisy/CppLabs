cmake_minimum_required(VERSION 3.20)
project(testes)

set(CMAKE_CXX_STANDARD 20)

set(ASTROID ../application/model/Astroid.cpp)
set(SOURCES ${ASTROID} test0.cpp)
#include_directories(/usr/local/include/)

add_executable(testes ${SOURCES})

add_executable(fixes fixes.cpp ${ASTROID})
