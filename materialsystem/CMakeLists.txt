cmake_minimum_required(VERSION 4.0)
project(materialsystem)
add_library(materialsystem SHARED
        CColorCorrection.cpp
		cmaterial.cpp
		cmaterial_queuefriendly.cpp
		CMaterialSubRect.cpp
		cmaterialvar.cpp
		cmatnullrendercontext.cpp
		colorspace.cpp
		ctexture.cpp
		../public/filesystem_helpers.cpp
		imagepacker.cpp
		mat_stub.cpp
		materialsystem_global.cpp
		morph.cpp
		occlusionquerymgr.cpp
		shadersystem.cpp
		texturemanager.cpp
		pch_materialsystem.cpp
		cmaterialdict.cpp
		cmaterialsystem.cpp
		cmatlightmaps.cpp
		cmatrendercontext.cpp
		cmatqueuedrendercontext.cpp
		ctexturecompositor.cpp
		../public/tier0/memoverride.cpp
)

target_compile_definitions(materialsystem PUBLIC DEFINE_MATERIALSYSTEM_INTERFACE MATERIALSYSTEM_EXPORTS)
find_package(SDL3 REQUIRED)
target_include_directories(appframework PUBLIC SDL3::SDL3) # why?

add_dependencies(materialsystem tier0 tier1 tier2 vstdlib mathlib bitmap shaderlib vtf)
target_link_libraries(materialsystem PUBLIC tier0 tier1 tier2 vstdlib mathlib bitmap shaderlib vtf)

install(TARGETS materialsystem DESTINATION bin)