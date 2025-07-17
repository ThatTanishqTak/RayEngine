cmake_minimum_required(VERSION 3.20)

project(RayEngine VERSION 0.1.0 LANGUAGES CXX)

# ----------------------------------------------------------------------------
# Options
# ----------------------------------------------------------------------------
option(RAYENGINE_BUILD_SHARED "Build RayEngine as a shared library (DLL)" ON)
option(RAYENGINE_USE_PRECOMPILED_HEADERS "Enable precompiled headers (raypch.h)" ON)

# No compiler extensions (/std:c++17 not gnu++17, etc.)
set(CMAKE_CXX_EXTENSIONS OFF)

# ----------------------------------------------------------------------------
# Locate prebuilt raylib
# ----------------------------------------------------------------------------
set(RAYLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib"
    CACHE PATH "Root of prebuilt raylib (must contain include/raylib.h and lib/)")

if(NOT EXISTS "${RAYLIB_ROOT}/include/raylib.h")
  message(FATAL_ERROR "raylib not found at ${RAYLIB_ROOT} (missing include/raylib.h). "
                      "Set RAYLIB_ROOT in the CMake cache.")
endif()

# Architecture subfolder heuristic (x64 vs x86) in common vendor layouts
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(_RAYLIB_ARCH x64)
else()
  set(_RAYLIB_ARCH x86)
endif()

set(_RAYLIB_LIB_HINTS
  "${RAYLIB_ROOT}/lib"
  "${RAYLIB_ROOT}/lib/${_RAYLIB_ARCH}"
  "${RAYLIB_ROOT}/lib/${_RAYLIB_ARCH}/Release"
  "${RAYLIB_ROOT}/lib/${_RAYLIB_ARCH}/Debug"
  "${RAYLIB_ROOT}/lib/Release"
  "${RAYLIB_ROOT}/lib/Debug"
)

# Try to locate Release + Debug variants (fall back Debug->Release if absent)
find_library(RAYLIB_LIBRARY_RELEASE
  NAMES raylib raylib_static
  HINTS ${_RAYLIB_LIB_HINTS}
  NO_DEFAULT_PATH
)
find_library(RAYLIB_LIBRARY_DEBUG
  NAMES raylibd raylib_debug raylib
  HINTS ${_RAYLIB_LIB_HINTS}
  NO_DEFAULT_PATH
)

if(NOT RAYLIB_LIBRARY_RELEASE)
  message(FATAL_ERROR "Failed to locate prebuilt raylib library under ${RAYLIB_ROOT}/lib.")
endif()
if(NOT RAYLIB_LIBRARY_DEBUG)
  set(RAYLIB_LIBRARY_DEBUG "${RAYLIB_LIBRARY_RELEASE}")
endif()

# Imported target (GLOBAL so RayForge sees it)
add_library(raylib::raylib UNKNOWN IMPORTED GLOBAL)
set_target_properties(raylib::raylib PROPERTIES
  IMPORTED_LOCATION_RELEASE "${RAYLIB_LIBRARY_RELEASE}"
  IMPORTED_LOCATION_DEBUG   "${RAYLIB_LIBRARY_DEBUG}"
  INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_ROOT}/include"
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  MAP_IMPORTED_CONFIG_MINSIZEREL   Release
)

# ----------------------------------------------------------------------------
# spdlog (header‑only, vendored)
#   NOTE: cannot create an actual target with name containing '::'; use alias.
# ----------------------------------------------------------------------------
add_library(spdlog_header_only INTERFACE)
add_library(spdlog::spdlog_header_only ALIAS spdlog_header_only)
target_include_directories(spdlog_header_only INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include>
  $<INSTALL_INTERFACE:include>
)

# ----------------------------------------------------------------------------
# Sources
#   CONFIGURE_DEPENDS => reconfigure when new source files are added.
# ----------------------------------------------------------------------------
file(GLOB_RECURSE RAYENGINE_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

# Optional: print them during configure for debugging (uncomment if needed)
# message(STATUS "RayEngine source files:")
# foreach(_src IN LISTS RAYENGINE_SOURCES)
#   message(STATUS "  ${_src}")
# endforeach()

# Pretty folder layout in Visual Studio
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${RAYENGINE_SOURCES})

# ----------------------------------------------------------------------------
# Library target
# ----------------------------------------------------------------------------
if(RAYENGINE_BUILD_SHARED)
  add_library(RayEngine SHARED ${RAYENGINE_SOURCES})
else()
  add_library(RayEngine STATIC ${RAYENGINE_SOURCES})
endif()
add_library(RayEngine::RayEngine ALIAS RayEngine)

# Require C++17 for consumers
target_compile_features(RayEngine PUBLIC cxx_std_17)

# Publish engine headers
target_include_directories(RayEngine
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# ----------------------------------------------------------------------------
# Link libraries
#   Explicit Win32 system libs recommended for static raylib builds.
#   Remove any you don't need; leaving them is harmless on Windows.
# ----------------------------------------------------------------------------
target_link_libraries(RayEngine
  PUBLIC
    raylib::raylib
    spdlog::spdlog_header_only
    $<$<PLATFORM_ID:Windows>:winmm>
    $<$<PLATFORM_ID:Windows>:gdi32>
    $<$<PLATFORM_ID:Windows>:opengl32>
    $<$<PLATFORM_ID:Windows>:user32>
    $<$<PLATFORM_ID:Windows>:shell32>
)

# ----------------------------------------------------------------------------
# Output directories (integrate with top‑level RAY_OUTPUT_BASE)
# ----------------------------------------------------------------------------
set(RAYENGINE_OUTPUT_BASE "${RAY_OUTPUT_BASE}" CACHE PATH "Base output directory for RayEngine artifacts")
set_target_properties(RayEngine PROPERTIES
  OUTPUT_NAME "RayEngine"
  WINDOWS_EXPORT_ALL_SYMBOLS ON
  RUNTIME_OUTPUT_DIRECTORY "${RAYENGINE_OUTPUT_BASE}/bin"
  LIBRARY_OUTPUT_DIRECTORY "${RAYENGINE_OUTPUT_BASE}/lib"
  ARCHIVE_OUTPUT_DIRECTORY "${RAYENGINE_OUTPUT_BASE}/lib"
)
if(CMAKE_CONFIGURATION_TYPES) # multi‑config (VS, etc.)
  foreach(_cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER "${_cfg}" _CFG_UC)
    set_target_properties(RayEngine PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY_${_CFG_UC} "${RAYENGINE_OUTPUT_BASE}/bin/${_cfg}"
      LIBRARY_OUTPUT_DIRECTORY_${_CFG_UC} "${RAYENGINE_OUTPUT_BASE}/lib/${_cfg}"
      ARCHIVE_OUTPUT_DIRECTORY_${_CFG_UC} "${RAYENGINE_OUTPUT_BASE}/lib/${_cfg}"
    )
  endforeach()
endif()

# ----------------------------------------------------------------------------
# Precompiled header
# ----------------------------------------------------------------------------
if(RAYENGINE_USE_PRECOMPILED_HEADERS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/raypch.h")
  target_precompile_headers(RayEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/raypch.h")
endif()

# ----------------------------------------------------------------------------
# Diagnostics
# ----------------------------------------------------------------------------
message(STATUS "RayEngine: raylib include: ${RAYLIB_ROOT}/include")
message(STATUS "RayEngine: raylib release: ${RAYLIB_LIBRARY_RELEASE}")
message(STATUS "RayEngine: raylib debug:   ${RAYLIB_LIBRARY_DEBUG}")