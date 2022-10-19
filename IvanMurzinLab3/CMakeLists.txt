cmake_minimum_required(VERSION 3.22)
project(lab3)

set(CMAKE_CXX_STANDARD 20)


include_directories(utils)

add_subdirectory(builder)
add_subdirectory(application)

add_executable(main main.cpp)








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
#TARGET_LINK_LIBRARIES(test ${LIBXL_LIB})
#TARGET_LINK_LIBRARIES(test ${LIBXL_LIB})
