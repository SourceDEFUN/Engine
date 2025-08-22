cmake_minimum_required(VERSION 4.0)
project(mathlib)
add_library(mathlib STATIC
        color_conversion.cpp
        halton.cpp
        lightdesc.cpp
        mathlib_base.cpp
        powsse.cpp
        sparse_convolution_noise.cpp
        sseconst.cpp
        sse.cpp
        ssenoise.cpp
        3dnow.cpp
        anorms.cpp
        bumpvects.cpp
        IceKey.cpp
        imagequant.cpp
        polyhedron.cpp
        quantize.cpp
        randsse.cpp
        spherical.cpp
        simdvectormatrix.cpp
        vector.cpp
        vmatrix.cpp
        almostequal.cpp
)

target_include_directories(mathlib PUBLIC ../public/mathlib)
target_compile_definitions(mathlib PUBLIC MATHLIB_LIB=1)