#pragma once

#include "FoxxoEngine/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace FoxxoEngine
{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

#define FOXE_CORE_FATAL(...) FoxxoEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define FOXE_CORE_ERROR(...) FoxxoEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FOXE_CORE_WARN(...)  FoxxoEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FOXE_CORE_INFO(...)  FoxxoEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FOXE_CORE_TRACE(...) FoxxoEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define FOXE_FATAL(...) FoxxoEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define FOXE_ERROR(...) FoxxoEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define FOXE_WARN(...)  FoxxoEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FOXE_INFO(...)  FoxxoEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define FOXE_TRACE(...) FoxxoEngine::Log::GetClientLogger()->trace(__VA_ARGS__)