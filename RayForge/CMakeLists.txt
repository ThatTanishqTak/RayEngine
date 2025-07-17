cmake_minimum_required(VERSION 3.20)

project(RayForge LANGUAGES CXX)

# ----------------------------------------------------------------------------
# Sources
# ----------------------------------------------------------------------------
file(GLOB_RECURSE RAYFORGE_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${RAYFORGE_SOURCES})

add_executable(RayForge ${RAYFORGE_SOURCES})
add_executable(RayForge::RayForge ALIAS RayForge)

# Require C++17 (editor code)
target_compile_features(RayForge PRIVATE cxx_std_17)

# Editor’s own headers (engine headers arrive transitively from link).
target_include_directories(RayForge
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Link to the engine (brings in raylib + spdlog + system libs)
target_link_libraries(RayForge
  PRIVATE
    RayEngine::RayEngine
)

# Hide console window in Release builds on MSVC (GUI app)
target_link_options(RayForge PRIVATE
  $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/SUBSYSTEM:WINDOWS>
  $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/ENTRY:mainCRTStartup>
)

# ----------------------------------------------------------------------------
# Output directories (workspace aligned)
# ----------------------------------------------------------------------------
set(RAYFORGE_OUTPUT_BASE "${RAY_OUTPUT_BASE}" CACHE PATH "Base output directory for RayForge artifacts")
set_target_properties(RayForge PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${RAYFORGE_OUTPUT_BASE}/bin"
  LIBRARY_OUTPUT_DIRECTORY "${RAYFORGE_OUTPUT_BASE}/lib"
  ARCHIVE_OUTPUT_DIRECTORY "${RAYFORGE_OUTPUT_BASE}/lib"
)
if(CMAKE_CONFIGURATION_TYPES)
  foreach(_cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER "${_cfg}" _CFG_UC)
    set_target_properties(RayForge PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY_${_CFG_UC} "${RAYFORGE_OUTPUT_BASE}/bin/${_cfg}"
      LIBRARY_OUTPUT_DIRECTORY_${_CFG_UC} "${RAYFORGE_OUTPUT_BASE}/lib/${_cfg}"
      ARCHIVE_OUTPUT_DIRECTORY_${_CFG_UC} "${RAYFORGE_OUTPUT_BASE}/lib/${_cfg}"
    )
  endforeach()
endif()

# For Visual Studio F5 debugging: run from the build/bin/<config> folder
set_property(TARGET RayForge PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
  "${RAYFORGE_OUTPUT_BASE}/bin/$<CONFIG>")