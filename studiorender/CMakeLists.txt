cmake_minimum_required(VERSION 4.0)
project(studiorender)
add_library(studiorender SHARED
        studiorender.cpp
		studiorendercontext.cpp
		flexrenderdata.cpp
		r_studio.cpp
		r_studiodecal.cpp
		r_studiodraw.cpp
		r_studiodraw_computeflexedvertex.cpp
		r_studioflex.cpp
		r_studiogettriangles.cpp
		r_studiolight.cpp
		r_studiostats.cpp
		../public/tier0/memoverride.cpp
)

target_compile_definitions(studiorender PUBLIC STUDIORENDER_EXPORTS)

add_dependencies(studiorender tier0 tier1 tier2 tier3 vstdlib mathlib bitmap)
target_link_libraries(studiorender PUBLIC tier0 tier1 tier2 tier3 vstdlib mathlib bitmap)

install(TARGETS studiorender DESTINATION bin)