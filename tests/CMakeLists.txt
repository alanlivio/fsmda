include_directories(${LIBPLATINUMKIT_INCLUDE_DIRS})
include_directories(${LIBXML2_INCLUDE_DIRS})
include_directories(${LIBZIP_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

#fake_parent_helper
add_executable(fake_parent_helper fake_parent_helper.cc)
target_link_libraries(fake_parent_helper fsmda)
target_link_libraries(fake_parent_helper ${LIBPLATINUMKIT_LIBRARIES})
target_link_libraries(fake_parent_helper ${LIBXML2_LIBRARIES})
target_link_libraries(fake_parent_helper ${LIBZIP_LIBRARIES})
target_link_libraries(fake_parent_helper ${GTEST_LIBRARIES})
target_link_libraries(fake_parent_helper ${GFLAGS_LIBRARIES})

# fake_child_helper
add_executable(fake_child_helper fake_child_helper.cc)
target_link_libraries(fake_child_helper fsmda)
target_link_libraries(fake_child_helper ${LIBPLATINUMKIT_LIBRARIES})
target_link_libraries(fake_child_helper ${LIBXML2_LIBRARIES})
target_link_libraries(fake_child_helper ${LIBZIP_LIBRARIES})
target_link_libraries(fake_child_helper ${GTEST_LIBRARIES})
target_link_libraries(fake_child_helper ${GFLAGS_LIBRARIES})

# testsuit
FILE(GLOB TESTSUIT_SRC_LIST *test.cc)
FILE(GLOB_RECURSE TESTSUIT_RSC_LIST files/*)
add_executable(testsuit ${TESTSUIT_SRC_LIST} ${TESTSUIT_RSC_LIST})
target_link_libraries(testsuit ${LIBPLATINUMKIT_LIBRARIES})
target_link_libraries(testsuit ${LIBXML2_LIBRARIES})
target_link_libraries(testsuit ${LIBZIP_LIBRARIES})
target_link_libraries(testsuit ${GTEST_LIBRARIES})
target_link_libraries(testsuit ${GFLAGS_LIBRARIES})
target_link_libraries(testsuit fsmda)

# tests
add_test(unittests testsuit)
