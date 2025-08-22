cmake_minimum_required(VERSION 4.0)
project(choreoobjects)
add_library(choreoobjects STATIC
        ../game/shared/choreoactor.cpp
        ../game/shared/choreochannel.cpp
        ../game/shared/choreoevent.cpp
        ../game/shared/choreoscene.cpp
        ../game/shared/sceneimage.cpp
)

target_include_directories(choreoobjects PUBLIC ../game/shared ../utils/common)