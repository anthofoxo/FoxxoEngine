workspace "FoxxoEngine"
    architecture "x64"

    configurations
    { "Debug", "Release", "Dist" }

    startproject "Sandbox"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "FoxxoEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "FoxxoEngine/vendor/Glad/include"
IncludeDir["imgui"] = "FoxxoEngine/vendor/imgui"

group "Dependencies"
    include "FoxxoEngine/vendor/GLFW"
    include "FoxxoEngine/vendor/Glad"
    include "FoxxoEngine/vendor/imgui"
group ""

project "FoxxoEngine"
    location "FoxxoEngine"
    kind "SharedLib"
    language "C++"
    staticruntime "Off"

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
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}"
    }

	links
	{
		"GLFW",
        "Glad",
        "imgui",
		"opengl32.lib"
	}

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "FOXE_PLATFORM_WINDOWS",
            "FOXE_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "FOXE_DEBUG"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines "FOXE_RELEASE"
        runtime "Release"
        optimize "On"
    
    filter "configurations:Dist"
        defines "FOXE_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        staticruntime "Off"
    
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

        links "FoxxoEngine"

        filter "system:windows"
            cppdialect "C++17"
            systemversion "latest"
            defines "FOXE_PLATFORM_WINDOWS"
    
        filter "configurations:Debug"
            defines "FOXE_DEBUG"
            runtime "Debug"
            symbols "On"
        
        filter "configurations:Release"
            defines "FOXE_RELEASE"
            runtime "Release"
            optimize "On"
        
        filter "configurations:Dist"
            defines "FOXE_DIST"
            runtime "Release"
            optimize "On"