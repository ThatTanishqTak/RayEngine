##--- RayEngine ---##

cmake_minimum_required(VERSION 3.20)
project(RayEngine LANGUAGES CXX)

# Defines

# Third-Party libraries
# Raylib dependency
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib)

# Engine sources
file(GLOB_RECURSE ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

# Build RayEngine as a shared library (.dll)
add_library(RayEngine SHARED
    ${ENGINE_SOURCES}
)

# Include directory
target_include_directories(RayEngine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Precompiled header
target_precompile_headers(RayEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/raypch.h
)

# Link libraries
target_link_libraries(RayEngine PUBLIC
    raylib
)