#pragma once

// raypch.h: Precompiled header for RayEngine
// Include stable headers here to speed up compilation across the project.

// NOTE: We intentionally avoid including <windows.h> to prevent name collisions
// with raylib C API functions (e.g., CloseWindow, ShowCursor). If Win32 APIs
// are needed, include <windows.h> in a separate platform-specific .cpp file before
// this header, keeping scope local.

// raylib header must come first so downstream headers can use its types safely
//#include <raylib.h>  // Core raylib functions for windowing, input, and graphics

// ---- C / C++ Standard Library Headers ----
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <limits>

#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <stdexcept> 

#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Engine utility headers
#include "RayEngine/Utilities/Utilities.h"  // Logging, helpers, and platform abstractions

// End of raypch.h