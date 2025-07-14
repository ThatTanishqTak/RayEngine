##--- Engine ---##

project(RayEngine LANGUAGES CXX)

# Defines

# Third-Party libraries


# Engine source files
file(GLOB_RECURSE ENGINE_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

# Build .dll
add_library(${PROJECT_NAME} SHARED 
    ${ENGINE_SOURCE}
)
# Include directory
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Set pre compiled header
#target_precompile_headers(${PROJECT_NAME} PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/.h
#)


# Link libraries
#target_link_libraries(${PROJECT_NAME} PUBLIC
#
#)