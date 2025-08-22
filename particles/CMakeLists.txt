cmake_minimum_required(VERSION 4.0)
project(particles)
add_library(particles STATIC
        builtin_constraints.cpp
        builtin_initializers.cpp
        builtin_particle_emitters.cpp
        builtin_particle_forces.cpp
        addbuiltin_ops.cpp
        builtin_particle_ops.cpp
        builtin_particle_render_ops.cpp
        particle_sort.cpp
        particles.cpp
        psheet.cpp
)