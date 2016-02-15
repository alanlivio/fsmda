# includes
include_directories(${LIBPLATINUM_INCLUDE_DIRS})
include_directories(${LIBXML2_INCLUDE_DIRS})
include_directories(${LIBZIP_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

# fsmda lib
file(GLOB_RECURSE SRC_LIST "fsmda/*.cc" "fsmda/*.h")
add_library(fsmda SHARED ${SRC_LIST})
target_link_libraries(fsmda ${LIBPLATINUM_LIBRARIES})
target_link_libraries(fsmda ${LIBXML2_LIBRARIES})
target_link_libraries(fsmda ${LIBZIP_LIBRARIES})
