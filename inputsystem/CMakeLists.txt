cmake_minimum_required(VERSION 4.0)
project(inputsystem)
add_library(inputsystem SHARED
        inputsystem.cpp
        joystick_sdl.cpp
        touch_sdl.cpp
        key_translation.cpp
        steamcontroller.cpp
        ../public/tier0/memoverride.cpp
)

add_dependencies(inputsystem tier0 tier1 tier2 vstdlib steam_api)
target_link_libraries(inputsystem PUBLIC tier0 tier1 tier2 vstdlib steam_api)

if(BUILD_SDL)
    target_compile_definitions(inputsystem PUBLIC USE_SDL=1)
    target_link_libraries(inputsystem PUBLIC tier0 tier1 tier2 vstdlib steam_api SDL3)
endif()

target_compile_definitions(inputsystem PUBLIC NO_STEAM)

if(WIN32)
    target_sources(inputsystem PUBLIC novint.cpp)
endif()

install(TARGETS inputsystem DESTINATION bin)