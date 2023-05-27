workspace "FilePacking"
	architecture "x64"
	targetdir "build"
	
	configurations 
	{ 
		"Debug", 
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AssetPacking"
    location "AssetPacking"
    kind "ConsoleApp"
    language "C++"
    
	targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/Source/**.h", 
		"%{prj.name}/Source/**.c", 
		"%{prj.name}/Source/**.hpp", 
		"%{prj.name}/Source/**.cpp" 
    }

    
	filter "system:windows"
		cppdialect "C++17"
        staticruntime "On"
        			
    filter "configurations:Debug"
        defines "RE_DEBUG"
		runtime "Debug"
        symbols "On"