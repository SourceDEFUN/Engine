cmake_minimum_required(VERSION 4.0)
project(tier2)
add_library(tier2 STATIC
        beamsegdraw.cpp
        defaultfilesystem.cpp
        dmconnect.cpp
        fileutils.cpp
        keybindings.cpp
        ../public/map_utils.cpp
        ../public/materialsystem/MaterialSystemUtil.cpp
        camerautils.cpp
        meshutils.cpp
        p4helpers.cpp
        renderutils.cpp
        riff.cpp
        soundutils.cpp
        tier2.cpp
        util_init.cpp
        utlstreambuffer.cpp
        vconfig.cpp
        keyvaluesmacros.cpp
)
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
target_include_directories(tier2 PRIVATE SDL3::SDL3 ../public/tier2)