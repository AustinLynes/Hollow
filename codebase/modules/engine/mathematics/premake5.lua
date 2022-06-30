project "mathematics"
    kind "staticLib"
    language "c++"
    cppdialect "c++latest"
    
    location "."

    configurations { "Debug",  "Release", "Distribution" }
    flags { "MultiProcessorCompile" }

   -- ../release/windows/debug/x64/
   outputdir = "%{cfg.system}/%{cfg.buildcfg}/%{cfg.architecture}"
    
    targetdir ("../../../release/" .. outputdir)
    objdir ("../../../release/" .. outputdir)

    files {
        "src/**.h",
        "src/**.cpp",
        "src/**.c"
    }

    includedirs {
        "src/", 
        "../../../packages/",
    }
    libdirs{
    }
    links {
    }

    filter "system:windows"   
        staticruntime "off"
        systemversion "latest"

        defines { "WIN32" }

    filter "configurations:Debug"
        symbols "on"
        buildoptions "/MDd"
        defines {  "_DEBUG", }
        
    filter "configurations:Release"
        optimize "on"
        symbols "off"
        buildoptions "/MD"

        defines { "NDEBUG" }



    filter "configurations:Distribution"
        defines {  "NDEBUG" }
        optimize "on"
        symbols "off"
        buildoptions "/MD"
