##--- Engine ---##

project(RayEngine LANGUAGES CXX)

# Defines

# Third-Party libraries
# Raylib dependency
add_subdirectory(vendor/raylib)

# Engine source files
file(GLOB_RECURSE ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

# Build RayEngine as a shared library (.dll)
add_library(${PROJECT_NAME} SHARED 
    ${ENGINE_SOURCES}
)

# Include directory
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Set pre compiled header
target_precompile_headers(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/raypch.h
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    raylib
)