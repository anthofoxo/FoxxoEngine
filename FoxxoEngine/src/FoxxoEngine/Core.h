#pragma once

#ifdef FOXE_PLATFORM_WINDOWS
	#ifdef FOXE_DLL
		#define FOXE_API __declspec(dllexport)
	#else
		#define FOXE_API __declspec(dllimport)
	#endif
#else
	#error FoxxoEngine only supports Windows!
#endif

#define BIT(x) (1 << x)