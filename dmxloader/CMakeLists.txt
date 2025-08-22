cmake_minimum_required(VERSION 4.0)
project(dmxloader)
add_library(dmxloader STATIC
        dmxattribute.cpp
        dmxelement.cpp
        dmxloader.cpp
        dmxloadertext.cpp
        dmxserializationdictionary.cpp
)