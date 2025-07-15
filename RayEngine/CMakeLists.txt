##--- RayEngine ---##

cmake_minimum_required(VERSION 3.20)
project(RayEngine LANGUAGES CXX)

# Defines

# Third-Party libraries
# Raylib dependency
set(RAYLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib" CACHE PATH "Path to prebuilt raylib")

# Imported raylib library
add_library(raylib STATIC IMPORTED GLOBAL)
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION "${RAYLIB_ROOT}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}raylib${CMAKE_STATIC_LIBRARY_SUFFIX}"
    INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_ROOT}/include"
)

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
    ${RAYLIB_ROOT}/include
)

# Library directories
target_link_directories(RayEngine PUBLIC
    ${RAYLIB_ROOT}/lib
)

# Precompiled header
target_precompile_headers(RayEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/raypch.h
)

# Link libraries
target_link_libraries(RayEngine PUBLIC
    raylib
    winmm.lib
)