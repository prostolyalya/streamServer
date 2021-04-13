cmake_minimum_required(VERSION 3.17)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
project(streamServer LANGUAGES CXX)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
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
    "sources/receiver.cpp"
    "sources/sender.cpp"
    "sources/connector.cpp"
    "sources/ui_controller.cpp"
    "sources/db_connector.cpp"
    "sources/cryptor.cpp"
    "sources/serializer.cpp"
    "sources/authentificator.cpp"
    "sources/blowfish_crypt.cpp"
)
set(HDRS_LIST
    "include/headers/server.h"
    "include/headers/thread_pool.h"
    "include/headers/client_manager.h"
    "include/headers/client.h"
    "include/headers/sender.h"
    "include/headers/receiver.h"
    "include/headers/connector.h"
    "include/headers/ui_controller.h"
    "include/headers/db_connector.h"
    "include/headers/cryptor.h"
    "include/headers/serializer.h"
    "include/headers/authentificator.h"
    "include/headers/blowfish_crypt.h"
)

find_package(QT NAMES Qt5 COMPONENTS Core Network Quick Sql REQUIRED)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network Quick Sql REQUIRED)
#find_package(Qt5 COMPONENTS Core Network Quick Sql REQUIRED)

add_executable(streamServer
  main.cpp
  ${SRC_LIST}
  ${HDRS_LIST}
)

target_link_libraries(streamServer Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql )
target_include_directories(streamServer PUBLIC include)
