cmake_minimum_required(VERSION 4.0)
project(vphysics)
add_library(vphysics SHARED
        convert.cpp
		../public/filesystem_helpers.cpp
		ledgewriter.cpp
		main.cpp
		physics_airboat.cpp
		physics_collide.cpp
		physics_constraint.cpp
		physics_controller_raycast_vehicle.cpp
		physics_environment.cpp
		physics_fluid.cpp
		physics_friction.cpp
		physics_material.cpp
		physics_motioncontroller.cpp
		physics_object.cpp
		physics_shadow.cpp
		physics_spring.cpp
		physics_vehicle.cpp
		physics_virtualmesh.cpp
		trace.cpp
		vcollide_parse.cpp
		vphysics_saverestore.cpp
		../public/tier0/memoverride.cpp
)

target_include_directories(vphysics PUBLIC ../ivp/ivp_intern ../ivp/ivp_collision ../ivp/ivp_physics ../ivp/ivp_surface_manager ../ivp/ivp_utility ../ivp/ivp_controller ../ivp/ivp_compact_builder ../ivp/havana/havok ../ivp/havana)
target_compile_definitions(vphysics PUBLIC VPHYSICS_EXPORTS HAVANA_CONSTRAINTS HAVOK_MOPP)

add_dependencies(vphysics tier0 tier1 tier2 vstdlib mathlib havana_constraints hk_math hk_base ivp_compactbuilder ivp_physics)
target_link_libraries(vphysics PUBLIC tier0 tier1 tier2 vstdlib mathlib havana_constraints hk_math hk_base ivp_compactbuilder ivp_physics)

install(TARGETS vphysics DESTINATION bin)