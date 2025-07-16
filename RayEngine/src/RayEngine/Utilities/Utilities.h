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