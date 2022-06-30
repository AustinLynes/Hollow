
-- modules
--      |  engine    
--              |  core    
--              |  graphics  
--              |  mathematics  
--              |  physics  
--      |  hollow    
-- *             |
--      |  tools    
--              |  editor    

project "hollow"
    kind "consoleApp"
    language "c++"
    cppdialect "c++latest"
    
    location "."

    configurations { "Debug",  "Release", "Distribution" }
    flags { "MultiProcessorCompile" }

   -- ../release/windows/debug/x64/
   outputdir = "%{cfg.system}/%{cfg.buildcfg}/%{cfg.architecture}"
    
    targetdir ("../../release/" .. outputdir)
    objdir ("../../release/" .. outputdir)

    files {
        "src/**.h",
        "src/**.cpp",
        "src/**.c",
        "../../dependencies/**.c", 
        "../../dependencies/**.cpp", 
        "../../dependencies/**.h", 
    }

    includedirs {
        "src/",
        "../../dependencies/", 
        "../../packages/",

        -- engine
        "../engine/core/src",      
        "../engine/graphics/src",
        "../engine/mathematics/src",
        
        -- tools layers
        "../tools/editor/src"
    }

    libdirs {
        "../../bin/lib/"
    }
    links {
        -- 
        "core",
        "mathematics",
        "graphics",

        -- tools
        "editor"
    }

    -- @echo copying
    -- xcopy /E /I "assets\\" "release/windows/Debug/x86_64\\" /Y
    filter "system:windows"
        staticruntime "off"
        systemversion "latest"
    
        defines { "WIN32" }
    
        postbuildcommands { 
            ("xcopy /E /I \"../../assets\\\\\" \"../../release/" .. outputdir .. "/assets/\\\\\" /Y ")
        }

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
