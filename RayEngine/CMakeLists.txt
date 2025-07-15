##--- RayEngine ---##

project(RayEngine LANGUAGES CXX)


# Defines

# Third-Party libraries
# Raylib dependency
add_library(raylib INTERFACE)
target_include_directories(raylib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/include>
)

# Engine sources
file(GLOB_RECURSE ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

# Build RayEngine as a shared library (.dll)
add_library(${PROJECT_NAME} SHARED
    ${ENGINE_SOURCES}
)

# Place the output DLL and import library next to the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

# Include directory
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Precompiled header
target_precompile_headers(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/raypch.h
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    raylib.lib
    $<$<PLATFORM_ID:Windows>:winmm.lib>
)