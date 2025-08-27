project(defunRmlUI)
cmake_minimum_required(VERSION 4.0)

#dont need to build this when building dedicated server
if( DEDICATED )
    return()
endif()

add_library(defunRmlUI Implementation.cpp System.cpp FileSystem.cpp)

if( POSIX )
    # OpenGL rendering implementation
    target_sources(${OUTBINNAME} PRIVATE RenderGL.cpp)
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
    target_link_libraries(${OUTBINNAME} SDL3::SDL3)
else()
    message(FATAL_ERROR "not implemented on windows for now")
endif()

target_link_libraries(defunRmlUI RmlCore RmlDebugger tier2 tier3 togl)