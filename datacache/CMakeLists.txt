cmake_minimum_required(VERSION 4.0)
project(datacache)
add_library(datacache SHARED
        datacache.cpp
        mdlcache.cpp
        ../public/studio.cpp
        ../public/studio_virtualmodel.cpp
        ../common/studiobyteswap.cpp
        ../public/tier0/memoverride.cpp
)

if(ANDROID EQUAL 1)
    target_link_libraries(datacache PUBLIC ANDROID_SUPPORT)
endif()

add_dependencies(datacache tier0 tier1 tier2 tier3)
target_link_libraries(datacache PUBLIC tier0 tier1 tier2 tier3)

install(TARGETS datacache DESTINATION bin)