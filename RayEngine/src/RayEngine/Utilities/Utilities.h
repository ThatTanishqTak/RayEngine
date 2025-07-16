#pragma once

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace RayEngine
{
	namespace Utilities
	{
		class Log
		{
		public:
			static void Init();

			static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
		};
	}
}

//template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
//inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
//{
//	return os << glm::to_string(vector);
//}
//
//template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
//inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
//{
//	return os << glm::to_string(matrix);
//}
//
//template<typename OStream, typename T, glm::qualifier Q>
//inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
//{
//	return os << glm::to_string(quaternion);
//}

// Core log macros
#define RAY_CORE_TRACE(...)    ::Trinity::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RAY_CORE_INFO(...)     ::Trinity::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RAY_CORE_WARN(...)     ::Trinity::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RAY_CORE_ERROR(...)    ::Trinity::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RAY_CORE_CRITICAL(...) ::Trinity::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define RAY_TRACE(...)         ::Trinity::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RAY_INFO(...)          ::Trinity::Log::GetClientLogger()->info(__VA_ARGS__)
#define RAY_WARN(...)          ::Trinity::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RAY_ERROR(...)         ::Trinity::Log::GetClientLogger()->error(__VA_ARGS__)
#define RAY_CRITICAL(...)      ::Trinity::Log::GetClientLogger()->critical(__VA_ARGS__)