#pragma once

#include "Core.h"
#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace FoxxoEngine
{
	class FOXE_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	};
}

// Core log macros
#define FOXE_CORE_FATAL(...) FoxxoEngine::Log::getCoreLogger()->fatal(__VA_ARGS__)
#define FOXE_CORE_ERROR(...) FoxxoEngine::Log::getCoreLogger()->error(__VA_ARGS__)
#define FOXE_CORE_WARN(...)  FoxxoEngine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define FOXE_CORE_INFO(...)  FoxxoEngine::Log::getCoreLogger()->info(__VA_ARGS__)
#define FOXE_CORE_TRACE(...) FoxxoEngine::Log::getCoreLogger()->trace(__VA_ARGS__)

// App log macros
#define FOXE_FATAL(...) FoxxoEngine::Log::getClientLogger()->fatal(__VA_ARGS__)
#define FOXE_ERROR(...) FoxxoEngine::Log::getClientLogger()->error(__VA_ARGS__)
#define FOXE_WARN(...)  FoxxoEngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define FOXE_INFO(...)  FoxxoEngine::Log::getClientLogger()->info(__VA_ARGS__)
#define FOXE_TRACE(...) FoxxoEngine::Log::getClientLogger()->trace(__VA_ARGS__)