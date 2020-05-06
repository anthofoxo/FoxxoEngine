#pragma once

#ifndef FOXE_PLATFORM_WINDOWS
	#error FoxxoEngine only supports Windows!
#endif

#ifdef FOXE_DEBUG
	#define FOXE_ENABLE_ASSERTS
#endif

#ifdef FOXE_ENABLE_ASSERTS
	#define FOXE_ASSERT(x, ...) { if(!(x)) { FOXE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FOXE_CORE_ASSERT(x, ...) { if(!(x)) { FOXE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FOXE_ASSERT(x, ...)
	#define FOXE_CORE_ASSERT(x, ...)
#endif

#define FOXE_BIT(x) (1 << x)

#define FOXE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)