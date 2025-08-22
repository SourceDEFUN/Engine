cmake_minimum_required(VERSION 4.0)
project(vtf)
add_library(vtf STATIC vtf.cpp)

if(WIN32)
    target_sources(vtf PUBLIC s3tc_decode.cpp)
endif()