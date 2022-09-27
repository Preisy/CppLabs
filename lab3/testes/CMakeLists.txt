cmake_minimum_required(VERSION 3.20)

project(testes)

include_directories(../application/model)

set(SOURCES_API ../application/model/Entities/terminal/Terminal.cpp
        ../application/model/Entities/terminal/InputTerminal.cpp
        ../application/model/Entities/terminal/OutputTerminal.cpp
        ../application/model/Entities/logicalElement/LogicalElement.cpp)

add_executable(test test.cpp ${SOURCES_API})
add_executable(fixes fixes.cpp ${SOURCES_API})