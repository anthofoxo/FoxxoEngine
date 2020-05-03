workspace "FoxxoEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "FoxxoEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "FoxxoEngine/vendor/Glad/include"

include "FoxxoEngine/vendor/GLFW"
include "FoxxoEngine/vendor/Glad"

project "FoxxoEngine"
    location "FoxxoEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "foxepch.h"
    pchsource "FoxxoEngine/src/foxepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
		"%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }

	links
	{
		"GLFW",
        "Glad",
		"opengl32.lib"
	}

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FOXE_PLATFORM_WINDOWS",
            "FOXE_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines
		{
			"FOXE_DEBUG",
			"FOXE_ENABLE_ASSERTS"
		}
        buildoptions "/MDd"
        symbols "On"
    
    filter "configurations:Release"
        defines "FOXE_RELEASE"
        buildoptions "/MD"
        optimize "On"
    
    filter "configurations:Dist"
        defines "FOXE_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
    
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
            "FoxxoEngine/src"
        }

        links
        {
            "FoxxoEngine"
        }
    
        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"
    
            defines
            {
                "FOXE_PLATFORM_WINDOWS"
            }
    
        filter "configurations:Debug"
            defines
			{
				"FOXE_DEBUG",
				"FOXE_ENABLE_ASSERTS"
			}
            buildoptions "/MDd"
            symbols "On"
        
        filter "configurations:Release"
            defines "FOXE_RELEASE"
            buildoptions "/MD"
            optimize "On"
        
        filter "configurations:Dist"
            defines "FOXE_DIST"
            buildoptions "/MD"
            optimize "On"