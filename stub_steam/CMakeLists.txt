cmake_minimum_required(VERSION 4.0)
project(stub_steam)
add_library(steam_api SHARED steam_api.cpp)
find_package(SDL3 REQUIRED)
target_include_directories(steam_api PUBLIC SDL3::SDL3)

install(TARGETS steam_api DESTINATION bin)