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
		"%{prj.name}/**.h", 
		"%{prj.name}/**.c", 
		"%{prj.name}/**.hpp", 
		"%{prj.name}/**.cpp" 
    }

    
	filter "system:windows"
		cppdialect "C++17"
        staticruntime "On"
        			
    filter "configurations:Debug"
        defines "RE_DEBUG"
		runtime "Debug"
        symbols "On"