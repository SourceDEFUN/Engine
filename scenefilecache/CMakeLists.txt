cmake_minimum_required(VERSION 4.0)
project(scenefilecache)
add_library(scenefilecache SHARED
        SceneFileCache.cpp
        ../public/tier0/memoverride.cpp
)

target_include_directories(scenefilecache PUBLIC ../game/shared)
target_compile_definitions(scenefilecache PUBLIC _WINDOWS=1) # what

add_dependencies(scenefilecache tier0 tier1)
target_link_libraries(scenefilecache PUBLIC tier0 tier1)

if(ANDROID EQUAL 1)
    target_link_libraries(scenefilecache PUBLIC ANDROID_SUPPORT)
endif()

install(TARGETS scenefilecache DESTINATION bin)