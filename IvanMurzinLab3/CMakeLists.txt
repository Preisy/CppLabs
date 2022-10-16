cmake_minimum_required(VERSION 3.22)
project(lab3)


include_directories(lib/model)
include_directories(lib/controller)

include_directories(model)
include_directories(controller)

set(CMAKE_CXX_STANDARD 20)


add_executable(lab3 lib/model/Action.cpp lib/controller/Dialog.cpp main.cpp model/Table.cpp model/Table.h model/Item.cpp model/Item.h controller/TableController.cpp controller/TableController.h)
#add_executable(ECode lib/model/Action.cpp lib/controller/Dialog.cpp ECode.cpp model/Table.cpp model/Table.h model/Item.cpp model/Item.h controller/TableController.cpp controller/TableController.h)
add_executable(ECode ECode.cpp model/Table.h model/Item.h)

add_executable(test test.cpp)
