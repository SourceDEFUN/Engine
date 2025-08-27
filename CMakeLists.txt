cmake_minimum_required(VERSION 4.0)
project(source_engine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## CONFIG

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fstrip")
else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
endif()

# TODO: unit tests
# TODO: add options for these
set(BUILD_DEDICATED OFF)
set(BUILD_SDL ON)
set(BUILD_OPUS ON)
set(BUILD_GL ON)
set(DEBUG_ENGINE OFF) # Enabling this is not recommended, as some things are missing.
set(DISABLE_WARNS OFF)

set(BUILD_GAME "hl2" CACHE STRING "What game to build: hl2, episodic, hl2mp, portal, hl1, hl1mp, cstrike, dod, tf")

# TODO: arm
if(NOT DEFINED ARCHITECTURE)
    if (CMAKE_SIZEOF_VOID_P GREATER 4)
        set(ARCHITECTURE 64bit)
    else()
        message(WARNING "32bit support might not work.")
        set(ARCHITECTURE 32bit)
    endif()
endif()

option(BUILD_DEDICATED "Build the dedicated server instead" OFF)
option(DEBUG_ENGINE "Build the engine in debug mode" OFF)
option(DISABLE_WARNS "Disable compiler warnings" OFF)

if(BUILD_DEDICATED)
    add_compile_definitions(DEDICATED=1)
    set(BUILD_SDL OFF)
endif()

if(BUILD_SDL)
    add_compile_definitions(USE_SDL=1)
endif()

if(BUILD_GL)
    add_compile_definitions(DX_TO_GL_ABSTRACTION GL_GLEXT_PROTOTYPES BINK_VIDEO)
    add_compile_definitions(TOGL) # TOGLES before.
endif()

if(ARCHITECTURE STREQUAL 64bit)
    add_compile_definitions(PLATFORM_64BITS=1)
endif()

add_compile_definitions(UseGUI_RmlUI) # TODO: make it changable in future!

# platform whitelist
if(LINUX)
    add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0 LINUX=1 _LINUX=1 POSIX=1 _POSIX=1 PLATFORM_POSIX=1 GNUC NO_HOOK_MALLOC _DLL_EXT=.so)
    add_compile_options(-U_FORTIFY_SOURCE)
elseif(ANDROID EQUAL 1)
    add_compile_definitions(ANDROID=1 _ANDROID=1 LINUX=1 _LINUX=1 POSIX=1 _POSIX=1 GNUC NO_HOOK_MALLOC _DLL_EXT=.so)
    add_compile_options(-funwind-tables)
elseif(WIN32)
    add_compile_definitions(WIN32=1 _WIN32=1 _WINDOWS _DLL_EXT=.dll _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE _ALLOW_RUNTIME_LIBRARY_MISMATCH _ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH _ALLOW_MSC_VER_MISMATCH NO_X360_XDK)
    link_libraries(user32 shell32 gdi32 advapi32 dbghelp psapi ws2_32 rpcrt4 winmm wininet ole32 shlwapi imm32)
    add_subdirectory(utils/bzip2)
    add_compile_options(/GF /Gy /fp:fast /Zc:forScope /Zc:wchar_t /GR /TP /EHsc)
elseif(APPLE)
    add_compile_definitions(OSX=1 _OSX=1 POSIX=1 _POSIX=1 PLATFORM_POSIX=1 GNUC NO_HOOK_MALLOC _DLL_EXT=.dylib)
    # TODO: frameworks
elseif(DEFINED BSD)
    add_compile_definitions(POSIX=1 _POSIX=1 PLATFORM_POSIX=1 GNUC PLATFORM_BSD=1 _DLL_EXT=.so)
endif()

# platform blacklist
if(NOT WIN32)
    add_compile_definitions(NO_MEMOVERRIDE_NEW_DELETE=1)
    add_compile_options(-pipe -fPIC)
    link_libraries(dl bz2 rt m)
    # add_compile_definitions(NO_MALLOC_OVERRIDE=1)
endif()
if(NOT MSVC)
    add_compile_options(-pthread)
endif()
if((NOT MSVC) AND (NOT APPLE))
    add_compile_options(-march=core2)
endif()
# TODO: ARM support

# debug
if(DEBUG_ENGINE)
    add_compile_definitions(DEBUG _DEBUG)
else()
    add_compile_definitions(NDEBUG)
endif()

# Disable VCR mode. Planning to remove it, as there's no reason for it (i do know what it's for)
# add_compile_definitions(NO_VCR) # Do not enable it yet, not every VCR use is covered in this define!

# TODO: GIT_COMMIT_HASH

# extra
if(DISABLE_WARNS)
    add_compile_options(-w)
else()
    add_compile_options(-Wall -fdiagnostics-color=always -Wcast-align -Wuninitialized -Winit-self -Wstrict-aliasing -Wno-reorder -Wno-unknown-pragmas -Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-value -Wno-unused-variable -faligned-new)
endif()

# any target
# -fnonconst-initializers
# TODO: msvc
add_compile_options(-fpermissive)
include_directories(AFTER ./ public common public/tier0 public/tier1)

# tests
#check_source_runs(C
#        "#include <ft2build.h>
#        #include FT_FREETYPE_H
#        int main() { return FT_Init_FreeType(0); }"
#        HAVE_FT2
#)
#check_source_runs(C
#        "#include <fontconfig/fontconfig.h>
#        #include FT_FREETYPE_H
#        int main() { return (int)(FcInit()); }"
#        HAVE_FC
#)

# default install path for non-game targets
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../Build/")
## PROJECTS

# common
add_subdirectory(appframework)
add_subdirectory(tier0)
add_subdirectory(tier1)
add_subdirectory(tier2)
add_subdirectory(tier3)
add_subdirectory(filesystem)
add_subdirectory(vpklib)
add_subdirectory(vstdlib)
add_subdirectory(bitmap)
add_subdirectory(choreoobjects)
add_subdirectory(datacache)
add_subdirectory(dmxloader)
add_subdirectory(engine)
add_subdirectory(game/server)
add_subdirectory(ivp/havana)
add_subdirectory(ivp/havana/havok/hk_base)
add_subdirectory(ivp/havana/havok/hk_math)
add_subdirectory(ivp/ivp_compact_builder)
add_subdirectory(ivp/ivp_physics)
add_subdirectory(materialsystem)
add_subdirectory(materialsystem/shaderlib)
add_subdirectory(soundemittersystem)
add_subdirectory(studiorender)
add_subdirectory(mathlib)
add_subdirectory(particles)
add_subdirectory(scenefilecache)
add_subdirectory(vgui2/vgui_controls)
add_subdirectory(vphysics)
add_subdirectory(vtf)
add_subdirectory(stub_steam)

## game only
if(NOT BUILD_DEDICATED)
    add_subdirectory(game/client)
    add_subdirectory(datamodel)
    add_subdirectory(engine/voice_codecs/minimp3)
    add_subdirectory(gameui)
    add_subdirectory(inputsystem)
    add_subdirectory(launcher)
    add_subdirectory(launcher_main)
    add_subdirectory(materialsystem/shaderapidx9)
    add_subdirectory(materialsystem/stdshaders)
    add_subdirectory(serverbrowser)
    add_subdirectory(vgui2/matsys_controls)
    add_subdirectory(vgui2/src)
    add_subdirectory(vgui2/vgui_surfacelib)
    add_subdirectory(vguimatsurface)
    add_subdirectory(utils/vtex)
    add_subdirectory(video)

    if(WIN32)
        add_subdirectory(unicode)
    endif ()

    if(BUILD_GL)
        add_subdirectory(togl) # togles before.
    endif()

    if(BUILD_OPUS OR (ANDROID EQUAL 1))
        add_subdirectory(engine/voice_codecs/opus)
    endif()
endif()

# dedicated only
if(BUILD_DEDICATED)
    add_subdirectory(dedicated)
    add_subdirectory(dedicated_main)
    add_subdirectory(materialsystem/shaderapiempty)
endif()