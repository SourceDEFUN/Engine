cmake_minimum_required(VERSION 4.0)
project(shaderapidx9)
add_library(shaderapidx9 SHARED
        colorformatdx8.cpp
        ../../public/filesystem_helpers.cpp
        hardwareconfig.cpp
        meshbase.cpp
        meshdx8.cpp
        shaderdevicebase.cpp
        shaderapibase.cpp
        shaderapidx8.cpp
        shaderdevicedx8.cpp
        shadershadowdx8.cpp
        texturedx8.cpp
        TransitionTable.cpp
        cvballoctracker.cpp
        vertexdecl.cpp
        vertexshaderdx8.cpp
        ../../public/tier0/memoverride.cpp
)

add_dependencies(shaderapidx9 tier0 tier1 tier2 vstdlib togl bitmap mathlib)
target_link_libraries(shaderapidx9 PUBLIC tier0 tier1 tier2 vstdlib togl bitmap mathlib)

if(NOT WIN32)
    target_sources(shaderapidx9 PUBLIC winutils.cpp)
endif()

if(ANDROID EQUAL 1)
    target_link_libraries(shaderapidx9 PUBLIC ANDROID_SUPPORT)
elseif(WIN32 AND (NOT BUILD_GL))
    target_sources(shaderapidx9 PUBLIC recording.cpp wmi.cpp)
    target_link_libraries(shaderapidx9 PUBLIC d3d9 d3dx9 bzip2)
endif()

target_compile_definitions(shaderapidx9 PUBLIC SHADER_DLL_EXPORT PROTECTED_THINGS_ENABLE)
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
target_include_directories(shaderapidx9 PUBLIC ./ ../../public ../../public/tier0 ../../public/tier1 ../../common ../ SDL3::SDL3)

install(TARGETS shaderapidx9 DESTINATION bin)