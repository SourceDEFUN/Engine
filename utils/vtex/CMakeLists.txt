cmake_minimum_required(VERSION 4.0)
project(vtex)
add_library(vtex_dll SHARED
        ../common/cmdlib.cpp
        ../../public/filesystem_helpers.cpp
        ../../public/filesystem_init.cpp
        ../common/filesystem_tools.cpp
        vtex.cpp
        ../../common/imageutils.cpp
)

target_include_directories(vtex_dll PUBLIC ./ ../ ../../ ../../public ../../public/tier0 ../../public/tier1 ../common ../../common ../../thirdparty)
target_compile_definitions(vtex_dll PUBLIC VTEX_DLL=1 UTILS=1 VTEX_DLL_EXPORTS=1 PROTECTED_THINGS_DISABLE=1)

add_dependencies(vtex_dll tier0 tier1 tier2 bitmap vstdlib mathlib vtf)
target_link_libraries(vtex_dll PUBLIC tier0 tier1 tier2 bitmap vstdlib mathlib vtf jpeg png z)

install(TARGETS vtex_dll DESTINATION bin)