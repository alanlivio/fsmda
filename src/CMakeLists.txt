# includes
include_directories(${LIBPLATINUMKIT_INCLUDE_DIRS})
include_directories(${LIBXML2_INCLUDE_DIRS})
include_directories(${LIBZIP_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

# fsmda lib
file(GLOB SRC_LIST "fsmda/*.cc" "fsmda/mode/*.cc" "fsmda/upnp/*.cc" "fsmda/utils/*.cc")
add_library(fsmda SHARED ${SRC_LIST})
target_link_libraries(fsmda ${LIBPLATINUMKIT_LIBRARIES})
target_link_libraries(fsmda ${LIBXML2_LIBRARIES})
target_link_libraries(fsmda ${LIBZIP_LIBRARIES})
