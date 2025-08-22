cmake_minimum_required(VERSION 4.0)
project(vgui_surfacelib)
add_library(vgui_surfacelib STATIC
        BitmapFont.cpp
        FontAmalgam.cpp
        FontManager.cpp
        FontEffects.cpp
)

find_package(Freetype REQUIRED)
find_package(Fontconfig REQUIRED)
target_include_directories(vgui_surfacelib PUBLIC ./ ../ ../../ ../../public/ ../../public/tier0 ../../public/tier1 ../../common
                                                Fontconfig::Fontconfig Freetype::Freetype ${FREETYPE_INCLUDE_DIRS} ${FONTCONFIG_INCLUDE_DIRS})

if(WIN32)
    target_sources(vgui_surfacelib PUBLIC Win32Font.cpp)
else ()
    target_sources(vgui_surfacelib PUBLIC linuxfont.cpp)
endif()