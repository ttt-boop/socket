cmake_minimum_required(VERSION 2.8)
project(hello)

set(CMAKE_CXX_STANDARD 11)

include_directories(./)

file(GLOB_RECURSE SOURCES "util/*.cpp" "socket/*.cpp")

add_executable(server ${SOURCES} server.cpp)
add_executable(client ${SOURCES} client.cpp)
#add_executable(test test.cpp ./util/Logger.cpp)
#add_executable(client client.cpp)