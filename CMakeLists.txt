# cmake configurations
#------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)
include(ExternalProject)
find_package(PkgConfig)
#set(CMAKE_VERBOSE_MAKEFILE on)
#set(CMAKE_CXX_FLAGS "-Wno-cpp")

# project configuration
#------------------------------------------------------------------
project(fsmda CXX C)
SET(PACKAGE "fsmda")
SET(PACKAGE_NAME ${PACKAGE})
SET(PACKAGE_VERSION_MAJOR "1")
SET(PACKAGE_VERSION_MINOR "0")
SET(VERSION "${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}")
SET(PACKAGE_VERSION ${VERSION})
SET(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")

# dependecies
#------------------------------------------------------------------
include("cmake/deps.cmake")

# fsmda and programs
#------------------------------------------------------------------
add_subdirectory(src)
add_subdirectory(programs)

# tests
#------------------------------------------------------------------
enable_testing()
add_subdirectory(tests)

# helpers targets
#------------------------------------------------------------------
include("cmake/distclean.cmake")
include("cmake/cpplint.cmake")
add_cpplint_target(src programs tests)

# final message
#------------------------------------------------------------------
message(STATUS "CMAKE_C_FLAGS:     " ${CMAKE_C_FLAGS})
message(STATUS "CMAKE_C_FLAGS:     " ${CMAKE_C_FLAGS})
message(STATUS "CMAKE_CXX_FLAGS:   " ${CMAKE_CXX_FLAGS})
message(STATUS "CMAKE_BINARY_DIR:  " ${CMAKE_BINARY_DIR})
message(STATUS "CMAKE_SOURCE_DIR:  " ${CMAKE_SOURCE_DIR})
message(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
message(STATUS "CMAKE_SYSTEM:      " ${CMAKE_SYSTEM} " "
 ${CMAKE_SYSTEM_PROCESSOR})


