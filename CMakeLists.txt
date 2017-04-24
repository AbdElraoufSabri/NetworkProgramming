cmake_minimum_required(VERSION 3.6)
project(NetworkProgramming)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SendFileClient src/SendFiles/client.cpp )
set(SendFileServer src/SendFiles/server.cpp )
add_executable(SendFileClient ${SendFileClient})
add_executable(SendFileServer ${SendFileServer})

set(MultiChatClient src/MultiChat/client.cpp)
set(MultiChatServer src/MultiChat/server.cpp)
add_executable(MultiChatClient ${MultiChatClient})
add_executable(MultiChatServer ${MultiChatServer})

configure_file(res/index.html index.html)