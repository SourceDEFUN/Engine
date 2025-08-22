cmake_minimum_required(VERSION 4.0)
project(launcher_main)
add_executable(hl2_launcher)

if(NOT (ANDROID EQUAL 1))
    target_sources(hl2_launcher PUBLIC main.cpp)
    target_include_directories(hl2_launcher PUBLIC ../public)

    if(WIN32)
        target_sources(hl2_launcher PUBLIC launcher_main.rc)
    else ()
        target_link_libraries(hl2_launcher PUBLIC dl)
    endif()
endif()

install(TARGETS hl2_launcher DESTINATION .)