workspace "Hollow"
    architecture "x64"
    
    configurations { "Debug",  "Release", "Distribution" }
    
    flags { "MultiProcessorCompile" }
    
    startproject "modules/hollow"

    -- engine modules
    project "physics"
    include "modules/engine/physics"
    
    project "mathematics"
    include "modules/engine/mathematics"
    
    project "graphics"
    include "modules/engine/graphics"
    
    project "core"
    include "modules/engine/core"    
    
    -- Tools
    project "editor"
    include "modules/tools/editor"    
    
    
    -- Executable 
    project "hollow"
    include "modules/hollow"
    
    -- -- tests
    -- project "tests"
    -- include "modules/tests"
