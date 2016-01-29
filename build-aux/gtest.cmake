set(GTEST_URL https://github.com/google/googletest/archive/release-1.7.0.zip)
set(GTEST_MD5 ef5e700c8a0f3ee123e2e0209b8b4961 )

if (NOT __GTEST_INCLUDED) # guard against multiple includes
  set(__GTEST_INCLUDED TRUE)

  # use the system-wide gtest if present
  find_package(GFlags QUIET)
  if (GTEST_FOUND)
    set(GTEST_EXTERNAL FALSE)
  else()
    if(EXISTS ${CMAKE_BINARY_DIR}/third_party/gtest)
        message(STATUS "Using gtest in ${CMAKE_BINARY_DIR}/third_party/libgest.")
    else()
        message(STATUS "The libgest-config.cmake was not found.")
        message(STATUS "${GTEST_URL} will be fetch and build.")
    endif()

    find_package(Threads)

    # build directory
    set(gtest_PREFIX ${CMAKE_BINARY_DIR}/third_party/gtest)
    # install directory
    set(gtest_INSTALL ${CMAKE_BINARY_DIR}/third_party/gtest-install)

    # we build gtest statically, but want to link it into the caffe shared library
    # this requires position-independent code
    if (UNIX)
        set(GTEST_EXTRA_COMPILER_FLAGS "-fPIC")
    endif()

    set(GTEST_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${GTEST_EXTRA_COMPILER_FLAGS})
    set(GTEST_C_FLAGS ${CMAKE_C_FLAGS} ${GTEST_EXTRA_COMPILER_FLAGS})

    ExternalProject_Add(gtest
      PREFIX ${gtest_PREFIX}
      URL ${GTEST_URL}
      URL_MD5 ${GTEST_MD5}
      UPDATE_COMMAND ""
      INSTALL_DIR ${gtest_INSTALL}
      CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                 -DCMAKE_INSTALL_PREFIX=${gtest_INSTALL}
                 -DBUILD_SHARED_LIBS=OFF
                 -BUILD_CONFIG_TESTS=OFF
                 -DCMAKE_C_FLAGS=${GTEST_C_FLAGS}
                 -DCMAKE_CXX_FLAGS=${GTEST_CXX_FLAGS}
      LOG_DOWNLOAD 1
      LOG_INSTALL 1
      INSTALL_COMMAND ""
      )

    set(GTEST_FOUND TRUE)
    set(GTEST_INCLUDE_DIRS ${gtest_PREFIX}/src/gtest/include/)
    set(GTEST_LIBRARIES ${gtest_PREFIX}/src/gtest-build/libgtest.a ${CMAKE_THREAD_LIBS_INIT})
    set(GTEST_LIBRARY_DIRS ${gtest_PREFIX}/src/gtest-build/)
    set(GTEST_EXTERNAL TRUE)

    list(APPEND external_project_dependencies gtest)
  endif()

endif()
