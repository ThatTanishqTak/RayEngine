cmake_minimum_required(VERSION 3.20)

# Top‑level workspace (aggregates RayEngine library + RayForge editor)
project(RayEngineWorkspace LANGUAGES CXX)

# ----------------------------------------------------------------------------
# Common lightweight Windows headers + macro hygiene
# ----------------------------------------------------------------------------
add_compile_definitions(
  WIN32_LEAN_AND_MEAN
  NOMINMAX
  NOGDI
  _WIN32
)

# Helpful MSVC build flags: parallel build & UTF‑8 source encoding
if(MSVC)
  add_compile_options(/MP /utf-8)
endif()

# ----------------------------------------------------------------------------
# Unified output base directory used by subprojects
# ----------------------------------------------------------------------------
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x64")
else()
    set(ARCH "x86")
endif()
set(RAY_OUTPUT_BASE "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${ARCH}/${PROJECT_NAME}" CACHE PATH
    "Base directory for all build outputs (bin/lib per-config).")
mark_as_advanced(RAY_OUTPUT_BASE)

# ----------------------------------------------------------------------------
# (Optional) Force MSVC runtime to match prebuilt raylib
#   Uncomment **one** of the following if you see CRT mismatch warnings
#   (LNK4098) and you know which flavor raylib was built with.
# ----------------------------------------------------------------------------
# if(MSVC)
#   set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")       # /MT,/MTd
#   #set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")   # /MD,/MDd
# endif()

# ----------------------------------------------------------------------------
# Subprojects
# ----------------------------------------------------------------------------
add_subdirectory(RayEngine)
add_subdirectory(RayForge)