cmake_minimum_required(VERSION 4.0)
project(bitmap)
add_library(bitmap STATIC
        ImageByteSwap.cpp
        colorconversion.cpp
        float_bm.cpp
        float_bm2.cpp
        float_bm3.cpp
        float_bm_bilateral_filter.cpp
        float_cube.cpp
        imageformat.cpp
        psd.cpp
        resample.cpp
        tgaloader.cpp
        tgawriter.cpp
        bitmap.cpp
)
if(WIN32)
    target_sources(bitmap PUBLIC float_bm4.cpp)
endif()