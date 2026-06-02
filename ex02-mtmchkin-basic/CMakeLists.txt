cmake_minimum_required(VERSION 3.24)
project(HW3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW3
        .idea/.gitignore
        .idea/HW3.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/workspace.xml
        Card.cpp
        Card.h
        Mtmchkin.cpp
        Mtmchkin.h
        Player.cpp
        Player.h
        utilities.cpp
        utilities.h)
