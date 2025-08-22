cmake_minimum_required(VERSION 4.0)
project(dedicated_main)
add_executable(dedicated_launcher main.cpp)

target_include_directories(dedicated_launcher PUBLIC ../public ../public/tier0)

if(NOT WIN32)
    target_link_libraries(dedicated_launcher PUBLIC dl)
else()
    target_link_libraries(dedicated_launcher PUBLIC user32 shell32)
    target_sources(dedicated_launcher PUBLIC dedicated_main.rc)
endif()

install(TARGETS dedicated_main DESTINATION .)