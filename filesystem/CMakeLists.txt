cmake_minimum_required(VERSION 4.0)
project(filesystem)
add_library(filesystem_stdio SHARED
        basefilesystem.cpp
        packfile.cpp
        filetracker.cpp
        filesystem_async.cpp
        filesystem_stdio.cpp
        ../public/kevvaluescompiler.cpp
        ../public/zip_utils.cpp
        QueuedLoader.cpp
        ../public/tier0/memoverride.cpp
)

add_dependencies(filesystem_stdio tier0 vpklib tier1 tier2 vstdlib)
target_link_libraries(filesystem_stdio PUBLIC tier0 vpklib tier1 tier2 vstdlib)
target_compile_definitions(filesystem_stdio PUBLIC FILESYSTEM_STDIO_EXPORTS=1 DONT_PROTECT_FILEIO_FUNCTIONS=1 SUPPORT_PACKED_STORE=1)

if(NOT WIN32)
    target_sources(filesystem_stdio PUBLIC linux_support.cpp)
endif()

install(TARGETS filesystem_stdio DESTINATION bin)