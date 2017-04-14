cmake_minimum_required(VERSION 3.6)
project(NetworkProgramming)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(Client src/client.cpp)
set(Server src/server.cpp)
add_executable(Client ${Client})
add_executable(Server ${Server})

configure_file(src/index.html index.html)