workspace "cpp-CoreApp-project-template-with-OpenGL-and-ImGui"
    architecture "x64"        
    startproject "App"
    
    configurations 
    {
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "Core/vendor/GLFW/include"
    IncludeDir["Glad"] = "Core/vendor/Glad/include"
    IncludeDir["glm"] = "Core/vendor/glm"
    IncludeDir["assimp"] = "Core/vendor/assimp/include"
    IncludeDir["ImGui"] = "Core/vendor/imgui"
    IncludeDir["stb_image"] = "Core/vendor/stb_image"
    IncludeDir["spdlog"] = "Core/vendor/spdlog/include"

    include "Core/vendor/Glad"
    include "Core/vendor/GLFW"

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
        "%{prj.name}/vendor/glm/glm/*.hpp",
        "%{prj.name}/vendor/glm/glm/*.inl",
        "%{prj.name}/vendor/imgui/*.cpp",
        "%{prj.name}/vendor/imgui/backends/imgui_impl_glfw.cpp",
        "%{prj.name}/vendor/imgui/backends/imgui_impl_opengl3.cpp"
    }
    
    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/res",
        "%{prj.name}/src/Application",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links 
    {
        "GLFW",
        "Glad",
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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
    }

    filter {"configurations:Debug"}
        defines "_DEBUG"
        symbols "On"
        
    filter {"configurations:Release"}
        defines "_RELEASE"
        symbols "Off"
        optimize "On"
    