cmake_minimum_required(VERSION 4.0)
project(video)
add_library(video_services SHARED
        videoservices.cpp
        ../public/tier0/memoverride.cpp
)

add_dependencies(video_services tier0 tier1 tier2 tier3 vstdlib)
target_link_libraries(video_services PUBLIC tier0 tier1 tier2 tier3 vstdlib)
find_package(SDL3 REQUIRED)
target_include_directories(video_services PUBLIC SDL3::SDL3)

if(APPLE)
    target_link_libraries(video_services PUBLIC COREGRAPHICS)
elseif(WIN32)
    target_link_libraries(video_services PUBLIC user32)
endif()

install(TARGETS video_services DESTINATION bin)