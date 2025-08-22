cmake_minimum_required(VERSION 4.0)
project(vpklib)
add_library(vpklib STATIC packedstore.cpp ../common/simplebitstring.cpp)