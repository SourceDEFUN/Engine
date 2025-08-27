cmake_minimum_required(VERSION 4.0)
project(launcher_main)
add_executable(SourceDEFUN)

if(NOT (ANDROID EQUAL 1))
    target_sources(SourceDEFUN PUBLIC main.cpp)
    target_include_directories(SourceDEFUN PUBLIC ../public)

    if(WIN32)
        target_sources(SourceDEFUN PUBLIC launcher_main.rc)
    else ()
        target_link_libraries(SourceDEFUN PUBLIC dl)
    endif()
endif()

install(TARGETS SourceDEFUN DESTINATION .)