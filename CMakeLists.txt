# cmake configurations
#------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)
include(ExternalProject)
find_package(PkgConfig)
#set(CMAKE_VERBOSE_MAKEFILE on)
#set(CMAKE_CXX_FLAGS "-g -Wall")

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

# fsmda and programs
#------------------------------------------------------------------
# libplatinumkit
pkg_check_modules(LIBPLATINUMKIT REQUIRED libplatinumkit)
# libxml-2.0
pkg_check_modules(LIBXML2 REQUIRED libxml-2.0)
# libzip
pkg_check_modules(LIBZIP REQUIRED libzip)
# glog
include("build-aux/glog.cmake")
# gflags
include("build-aux/gflags.cmake")

add_subdirectory(src)
add_subdirectory(programs)

# tests
#------------------------------------------------------------------
# gtest
include("build-aux/gtest.cmake")

enable_testing()
add_subdirectory(tests)
