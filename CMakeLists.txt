cmake_minimum_required(VERSION 2.8)
project(hello)

set(CMAKE_CXX_STANDARD 11)

include_directories(./)

file(GLOB_RECURSE SOURCES "util/*.cpp" "socket/*.cpp" "socket/*.h")

add_executable(server ${SOURCES} server.cpp)
add_executable(client ${SOURCES} client.cpp)
add_executable(test ${SOURCES} test.cpp)
#add_executable(client client.cpp)