-- premake5.lua
workspace "LarkGUI"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "LarkGUI"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "WalnutExternal.lua"
include "LarkGUI"