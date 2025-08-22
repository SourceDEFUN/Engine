cmake_minimum_required(VERSION 4.0)
project(shaderlib)
add_library(shaderlib STATIC
        BaseShader.cpp
        ShaderDLL.cpp
        shaderlib_cvar.cpp
)

target_compile_definitions(shaderlib PUBLIC FAST_MATERIALVAR_ACCESS=1)
target_include_directories(shaderlib PUBLIC ./ ../ ../../public ../../public/tier0 ../../public/tier1 ../../common)