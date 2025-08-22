cmake_minimum_required(VERSION 4.0)
project(minimp3)
add_library(vaudio_minimp3 SHARED
        mp3codecs.cpp
        ../../../public/tier0/memoverride.cpp
)

add_dependencies(vaudio_minimp3 tier0 tier1 vstdlib)
target_link_libraries(vaudio_minimp3 PUBLIC tier0 tier1 vstdlib)

target_include_directories(vaudio_minimp3 PUBLIC ./ ../../../public/tier1 ../../../public ../../../Thirdparty/minimp3)

install(TARGETS vaudio_minimp3 DESTINATION bin)