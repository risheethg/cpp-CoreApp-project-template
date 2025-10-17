workspace "cpp-CoreApp-project-template"
    architecture "x64"        
    startproject "App"
    
    configurations 
    {
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["spdlog"] = "Core/vendor/spdlog/include"

project "Core"
    location "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir("bin/" ..outputdir.. "/%{prj.name}")
    objdir("bin-int/" ..outputdir.. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "Core/src/Application/pch.cpp"
    
    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Application/**.h",
        "%{prj.name}/Application/**.cpp",
    }
    
    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/res",
        "%{prj.name}/src/Application",
        "%{IncludeDir.spdlog}",
    }
    

    defines 
    {
        "ENABLE_ASSERTS",
    }

    filter {"configurations:Debug"}
        defines "_DEBUG"
        symbols "On"
        
    filter {"configurations:Release"}
        defines "_RELEASE"
        symbols "Off"
        optimize "On"
    
    
project "App"
    location "App"
    architecture "x64"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir("bin/" ..outputdir.. "/%{prj.name}")
    objdir("bin-int/" ..outputdir.. "/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    links 
    {
        "Core"
    }

    includedirs 
    {
        "%{prj.name}/src",
        "%{wks.location}/Core/src", 
        "%{IncludeDir.spdlog}",
    }

    filter {"configurations:Debug"}
        defines "_DEBUG"
        symbols "On"
        
    filter {"configurations:Release"}
        defines "_RELEASE"
        symbols "Off"
        optimize "On"
    