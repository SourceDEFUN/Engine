cmake_minimum_required(VERSION 4.0)
project(dedicated)
add_library(dedicated SHARED
        filesystem.cpp
        ../public/filesystem_init.cpp
        ../common/netapi.cpp
        ../common/SteamAppStartup.cpp
        sys_common.cpp
        sys_ded.cpp
        console/conproc.cpp
        console/textconsole.cpp
        ../filesystem/filetracker.cpp
        ../filesystem/basefilesystem.cpp
        ../filesystem/packfile.cpp
        ../filesystem/filesystem_async.cpp
        ../filesystem/filesystem_stdio.cpp
        ../filesystem/QueuedLoader.cpp
        ../public/zip_utils.cpp
        ../public/tier0/memoverride.cpp
)

if(WIN32)
    target_sources(dedicated PUBLIC
            sys_windows.cpp
            vgui/CreateMultiplayerGameServerPage.cpp
            vgui/MainPanel.cpp
            ../public/vgui_controls/vgui_controls.cpp
            vgui/vguihelpers.cpp
            console/TextConsoleWin32.cpp
    )
    add_dependencies(dedicated vgui_controls)
    target_link_libraries(dedicated PUBLIC vgui_controls)
else()
    target_sources(dedicated PUBLIC
            sys_linux.cpp
            console/TextConsoleUnix.cpp
            ../filesystem/linux_support.cpp
    )
endif()

target_compile_definitions(dedicated PUBLIC LAUNCHERONLY=1 SUPPORT_PACKED_STORE=1 DEDICATED=1)
find_package(SDL3 REQUIRED)
target_include_directories(appframework PUBLIC SDL3::SDL3)

add_dependencies(dedicated tier0 tier1 tier2 tier3 vstdlib steam_api appframework mathlib)
target_link_libraries(dedicated PUBLIC tier0 tier1 tier2 tier3 vstdlib steam_api appframework mathlib edit)

install(TARGETS dedicated DESTINATION bin)