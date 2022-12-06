cmake_minimum_required(VERSION 3.20)
project(application)

set(CMAKE_CXX_STANDARD 20)

include_directories(model)
include_directories(view)
include_directories(controller)

include_directories(presentation)


set(SOURCES_API)
set(SOURCES_PR presentation/Dialog.cpp)

add_executable(startup startup.cpp ${SOURCES_API} ${SOURCES_PR})

include_directories(../builder)
target_link_libraries(startup builder)



#set(XL_ROOT "${CMAKE_SOURCE_DIR}/libs/libxl-4.0.4.0/")
#set(XL_INC_DIR "${CMAKE_SOURCE_DIR}/libs/libxl-4.0.4.0/include_cpp")
#set(XL_LIB_DIR "${CMAKE_SOURCE_DIR}/libs/libxl-4.0.4.0/lib64")
#
#find_path(LIBXL_INC_DIR "libxl.h"
#        HINTS ${XL_INC_DIR}
#        )
#
#find_library(LIBXL_LIB NAMES xl
#        HINTS ${XL_LIB_DIR}
#        )
#
#INCLUDE_DIRECTORIES(${LIBXL_INC_DIR})
#
#TARGET_LINK_LIBRARIES(startup ${LIBXL_LIB})
