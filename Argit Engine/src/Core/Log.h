#pragma once

#include "Base.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

// Core log macros
#define HZ_CORE_TRACE(...)    ::Argit::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)     ::Argit::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)     ::Argit::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)    ::Argit::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...) ::Argit::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HZ_TRACE(...)         ::Argit::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)          ::Argit::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)          ::Argit::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)         ::Argit::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_CRITICAL(...)      ::Argit::Log::GetClientLogger()->critical(__VA_ARGS__)

namespace Argit {

	class Log
	{
	public:
		static void Init();

		static Reference<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Reference<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Reference<spdlog::logger> s_CoreLogger;
		static Reference<spdlog::logger> s_ClientLogger;
	};

}

