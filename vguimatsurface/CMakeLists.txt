cmake_minimum_required(VERSION 4.0)
project(vguimatsurface)
add_library(vguimatsurface SHARED
        Clip2D.cpp
        Cursor.cpp
        ../public/filesystem_helpers.cpp
        FontTextureCache.cpp
        Input.cpp
        MatSystemSurface.cpp
        asanstubs.cpp
        TextureDictionary.cpp
        ../vgui2/src/vgui_key_translation.cpp
        ../public/vgui_controls/vgui_controls.cpp
        ../public/tier0/memoverride.cpp
)

target_include_directories(vguimatsurface PUBLIC ./ ../public ../public/tier0 ../public/tier1 ../common)
target_compile_definitions(vguimatsurface PUBLIC VGUIMATSURFACE_DLL_EXPORT=1 GAMEUI_EXPORTS=1 DONT_PROTECT_FILEIO_FUNCTIONS=1)

add_dependencies(vguimatsurface bitmap mathlib tier0 vgui_controls tier1 vstdlib tier2 tier3 vgui_surfacelib)
find_package(Freetype REQUIRED)
target_link_libraries(vguimatsurface PUBLIC bitmap mathlib tier0 vgui_controls tier1 vstdlib tier2 tier3 vgui_surfacelib Freetype::Freetype fontconfig SDL3)

if(WIN32)
    target_sources(vguimatsurface PUBLIC memorybitmap.cpp)
elseif(ANDROID EQUAL 1)
    target_link_libraries(vguimatsurface PUBLIC EXPAT)
endif()

install(TARGETS vguimatsurface DESTINATION bin)