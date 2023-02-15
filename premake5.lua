-- premake5.lua
require "clion"

workspace "SleepyForest"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "SleepyForest"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "SleepyForest"
