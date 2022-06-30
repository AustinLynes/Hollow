project "editor"
    kind "staticLib"
    language "c++"
    cppdialect "c++latest"
    
    location "."   

    -- ../release/windows/debug/x64/
    outputdir = "%{cfg.system}/%{cfg.buildcfg}/%{cfg.architecture}"
    
    targetdir ("../../../release/" .. outputdir)
    objdir ("../../../release/" .. outputdir)

    files {
        "src/**.h",
        "src/**.cpp",
        "src/**.c"
    }

    -- modules
    --      |  engine    
    --              |  core    
    --              |  graphics  
    --              |  mathematics  
    --              |  physics  
    --      |  hollow    
    --              |
    --      |  tools    
    -- *             |  editor    

    includedirs {
        "src/",
        "../../../packages/",

        -- core engine
        "../../engine/core/src",      
        "../../engine/graphics/src",
        "../../engine/mathematics/src",

    }
    libdirs{
        "../../../bin/lib/%{cfg.buildcfg}/"
    }
    links {
        "core",
        "mathematics",
        "graphics"
    }
    defines {
        
    }


    filter "system:windows"
        staticruntime "off"
        systemversion "latest"

        defines {
            "WIN32",
        }
    filter "configurations:Debug"
        defines { 
            "_DEBUG"
        }
        symbols "on"
        buildoptions "/MDd"
        
    filter "configurations:Release"
        optimize "on"
        symbols "off"
        buildoptions "/MD"

        defines { "NDEBUG" }

    filter "configurations:Release"
        defines {
            "NDEBUG"
        }
        optimize "on"
        symbols "off"
        buildoptions "/MD"
    
