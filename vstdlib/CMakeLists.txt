cmake_minimum_required(VERSION 4.0)
project(vstdlib)
add_library(vstdlib SHARED
        coroutine.cpp
        cvar.cpp
        jobthread.cpp
        KeyValuesSystem.cpp
        random.cpp
        vcover.cpp
        ../public/tier0/memoverride.cpp
)

add_dependencies(vstdlib tier0 tier1)
target_link_libraries(vstdlib tier0 tier1)

if(WIN32)
    target_sources(vstdlib PUBLIC processutils.cpp)
    if(ARCHITECTURE STREQUAL 64bits)
        target_sources(vstdlib PUBLIC coroutine_win64.masm getstackptr64.masm) # TODO: rewrite in proper assembler syntax
    endif()
elseif(ANDROID EQUAL 1)
    target_link_libraries(vstdlib PUBLIC ANDROID_SUPPORT) # what?
elseif(APPLE)
    target_compile_options(-framework CoreServices)
endif()

install(TARGETS vstdlib DESTINATION bin)