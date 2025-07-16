##--- RayForge ---##

cmake_minimum_required(VERSION 3.20)
project(RayForge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect editor source files
file(GLOB_RECURSE EDITOR_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

# Build the executable
add_executable(${PROJECT_NAME} ${EDITOR_SOURCES})

# Set custom output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

# Turn off the console window for release build
target_link_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>
    $<$<CONFIG:Release>:/ENTRY:mainCRTStartup>
)

# Include directory
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/RayEngine/src
)

# Link against the engine
target_link_libraries(${PROJECT_NAME} PRIVATE 
    RayEngine
)