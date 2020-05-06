workspace "FoxxoEngine"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "Sandbox"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "FoxxoEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "FoxxoEngine/vendor/Glad/include"
IncludeDir["imgui"] = "FoxxoEngine/vendor/imgui"
IncludeDir["glm"] = "FoxxoEngine/vendor/glm"

group "Dependencies"
	include "FoxxoEngine/vendor/GLFW"
	include "FoxxoEngine/vendor/Glad"
	include "FoxxoEngine/vendor/imgui"
group ""

project "FoxxoEngine"
	location "FoxxoEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "foxepch.h"
	pchsource "FoxxoEngine/src/foxepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines "_CRT_SECURE_NO_WARNINGS"

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FOXE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FOXE_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "FOXE_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "FOXE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"FoxxoEngine/vendor/spdlog/include",
		"FoxxoEngine/src",
		"FoxxoEngine/vendor",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}"
	}

	links "FoxxoEngine"

	filter "system:windows"
		systemversion "latest"
		defines "FOXE_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines "FOXE_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "FOXE_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "FOXE_DIST"
		runtime "Release"
		optimize "on"