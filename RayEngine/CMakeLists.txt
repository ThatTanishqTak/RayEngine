##--- RayEngine ---##

cmake_minimum_required(VERSION 3.20)
project(RayEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Third-Party libraries
# Raylib dependency
set(RAYLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib" CACHE PATH "Path to prebuilt raylib")

if(NOT EXISTS "${RAYLIB_ROOT}/include/raylib.h")
    message(FATAL_ERROR "raylib not found. Set RAYLIB_ROOT to a valid raylib installation")
endif()

add_library(raylib STATIC IMPORTED GLOBAL)
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION "${RAYLIB_ROOT}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}raylib${CMAKE_STATIC_LIBRARY_SUFFIX}"
    INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_ROOT}/include"
)

# spdlog
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include>
)

# Collect engine source files
file(GLOB_RECURSE ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

# Build the .dll
add_library(${PROJECT_NAME} SHARED 
    ${ENGINE_SOURCES}
)

# Set the custom output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)


# Include directory
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    ${RAYLIB_ROOT}/include  # Propagate raylib includes
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    raylib
    winmm.lib
    spdlog
)

# Set precompiled header
target_precompile_headers(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/raypch.h
)