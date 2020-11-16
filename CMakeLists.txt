cmake_minimum_required(VERSION 3.17)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
project(streamServer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
)
set(SRC_LIST
    "sources/thread_pool.cpp"
    "sources/server.cpp"
    "sources/client_manager.cpp"
    "sources/client.cpp"
)
set(HDRS_LIST
    "include/headers/server.h"
    "include/headers/thread_pool.h"
    "include/headers/client_manager.h"
    "include/headers/client.h"
)
find_package(Qt5Core)

add_executable(streamServer
  main.cpp
  ${SRC_LIST}
  ${HDRS_LIST}
)
target_link_libraries(streamServer Qt${QT_VERSION_MAJOR}::Core)
target_include_directories(streamServer PUBLIC include)
