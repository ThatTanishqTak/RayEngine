#pragma once

// -----------------------------------------------------------------------------
// Local Win32 shim for spdlog
// -----------------------------------------------------------------------------
// spdlog's Windows color sink includes <windows.h>, which in turn declares
// global C functions CloseWindow(), ShowCursor(), LoadImageA/W, DrawTextA/W, ...
// These clash with raylib's global C API names (CloseWindow(), ShowCursor(), ...).
//
// We temporarily macro-rename the Win32 identifiers so the Windows prototypes
// are parsed under unique names. We immediately undef them after including
// spdlog so the rest of the codebase isn't polluted.
//
// If you ever *need* the real Win32 APIs in code that includes this header,
// call them via the Windows prefix (::CloseWindow) from a TU that includes
// <windows.h> directly *before* raylib, or create platform wrappers.
// -----------------------------------------------------------------------------
#if defined(_WIN32)
#define CloseWindow    WIN32API_CloseWindow
#define ShowCursor     WIN32API_ShowCursor
#define LoadImage      WIN32API_LoadImage
#define LoadImageA     WIN32API_LoadImageA
#define LoadImageW     WIN32API_LoadImageW
#define DrawText       WIN32API_DrawText
#define DrawTextA      WIN32API_DrawTextA
#define DrawTextW      WIN32API_DrawTextW
#define DrawTextEx     WIN32API_DrawTextEx
#define DrawTextExA    WIN32API_DrawTextExA
#define DrawTextExW    WIN32API_DrawTextExW
#endif

// This ignores all warnings raised inside external headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#if defined(_WIN32)
#undef CloseWindow
#undef ShowCursor
#undef LoadImage
#undef LoadImageA
#undef LoadImageW
#undef DrawText
#undef DrawTextA
#undef DrawTextW
#undef DrawTextEx
#undef DrawTextExA
#undef DrawTextExW
#endif

namespace RayEngine
{
    namespace Utilities
    {
        class Log
        {
        public:
            static void Inititialize();
            inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;
        };
    }
}

// Core log macros
#define RAY_CORE_TRACE(...)    ::RayEngine::Utilities::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RAY_CORE_INFO(...)     ::RayEngine::Utilities::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RAY_CORE_WARN(...)     ::RayEngine::Utilities::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RAY_CORE_ERROR(...)    ::RayEngine::Utilities::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RAY_CORE_CRITICAL(...) ::RayEngine::Utilities::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define RAY_INFO(...)          ::RayEngine::Utilities::Log::GetClientLogger()->info(__VA_ARGS__)
#define RAY_TRACE(...)         ::RayEngine::Utilities::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RAY_WARN(...)          ::RayEngine::Utilities::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RAY_ERROR(...)         ::RayEngine::Utilities::Log::GetClientLogger()->error(__VA_ARGS__)
#define RAY_CRITICAL(...)      ::RayEngine::Utilities::Log::GetClientLogger()->critical(__VA_ARGS__)