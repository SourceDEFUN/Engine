cmake_minimum_required(VERSION 4.0)
project(soundemittersystem)
add_library(soundemittersystem SHARED
        ../game/shared/interval.cpp
        soundemittersystembase.cpp
        ../public/SoundParametersInternal.cpp
        ../public/tier0/memoverride.cpp
)

target_include_directories(soundemittersystem PUBLIC ./ ../ ../public/tier0 ../public/tier1 ../game/shared)
target_compile_definitions(soundemittersystem PUBLIC SOUNDEMITTERSYSTEM_EXPORTS=1 _WINDOWS=1)

add_dependencies(soundemittersystem tier0 tier1 vstdlib)
target_link_libraries(soundemittersystem PUBLIC tier0 tier1 vstdlib)

install(TARGETS soundemittersystem DESTINATION bin)