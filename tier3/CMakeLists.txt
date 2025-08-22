cmake_minimum_required(VERSION 4.0)
project(tier3)
add_library(tier3 STATIC
        tier3.cpp
        mdlutils.cpp
        choreoutils.cpp
        scenetokenprocessor.cpp
        studiohdrstub.cpp
)
target_include_directories(tier2 PRIVATE ../public/tier2 ../public/tier3)