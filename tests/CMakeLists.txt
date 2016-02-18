set(GTEST_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/gtest/include/)
include_directories(${LIBPLATINUM_INCLUDE_DIRS})
include_directories(${LIBXML2_INCLUDE_DIRS})
include_directories(${LIBZIP_INCLUDE_DIRS})
include_directories(${GFLAGS_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

# fake_parent_helper
add_executable(fake_parent_helper fake_parent_helper.cc)
target_link_libraries(fake_parent_helper fsmda)
target_link_libraries(fake_parent_helper ${LIBPLATINUM_LIBRARIES})
target_link_libraries(fake_parent_helper ${LIBXML2_LIBRARIES})
target_link_libraries(fake_parent_helper ${LIBZIP_LIBRARIES})
target_link_libraries(fake_parent_helper ${GFLAGS_LIBRARIES})

# fake_child_helper
add_executable(fake_child_helper fake_child_helper.cc)
target_link_libraries(fake_child_helper fsmda)
target_link_libraries(fake_child_helper ${LIBPLATINUM_LIBRARIES})
target_link_libraries(fake_child_helper ${LIBXML2_LIBRARIES})
target_link_libraries(fake_child_helper ${LIBZIP_LIBRARIES})
target_link_libraries(fake_child_helper ${GFLAGS_LIBRARIES})

# gtest_suit
FILE(GLOB TESTSUIT_SRC_LIST *test.cc gtest_suit.cc gtest/src/gtest-all.cc)
FILE(GLOB_RECURSE TESTSUIT_RSC_LIST files/*)
add_executable(gtest_suit ${TESTSUIT_SRC_LIST} ${TESTSUIT_RSC_LIST})
target_include_directories(gtest_suit PRIVATE ${CMAKE_CURRENT_LIST_DIR}/gtest/)
target_link_libraries(gtest_suit ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(gtest_suit ${LIBPLATINUM_LIBRARIES})
target_link_libraries(gtest_suit ${LIBXML2_LIBRARIES})
target_link_libraries(gtest_suit ${LIBZIP_LIBRARIES})
target_link_libraries(gtest_suit ${GFLAGS_LIBRARIES})
target_link_libraries(gtest_suit fsmda)

# tests
add_test(unittests gtest_suit)
