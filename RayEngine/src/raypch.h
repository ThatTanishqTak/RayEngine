#pragma once
//
// raypch.h  -- Precompiled header for RayEngine
//
// IMPORTANT: We intentionally do *not* include <windows.h> here to avoid
// name collisions with raylib global C functions (CloseWindow, ShowCursor, ...).
// If you ever need Win32 APIs, include <windows.h> *only* in a separate
// platform-specific .cpp that does NOT include this PCH, or include it
// before this header in that one .cpp and keep the scope local.
//

// raylib first (so downstream headers can safely use its types)
#include <raylib.h>

// ---- C / C++ std library ----
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

// Engine utilities
#include "RayEngine/Utilities/Utilities.h"