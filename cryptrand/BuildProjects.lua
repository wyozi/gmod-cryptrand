solution "gmsv_cryptrandom"

	language "C++"
	location ( os.get() .."-".. _ACTION )
	flags { "Symbols", "NoEditAndContinue", "NoPCH", "StaticRuntime", "EnableSSE" }
	targetdir ( "lib/" .. os.get() .. "/" )
	includedirs { "../include/" }

	if os.is("linux") then
		buildoptions "-std=c++0x"
	end
	
	configurations
	{ 
		"Release"
	}
	
	configuration "Release"
		defines { "NDEBUG" }
		flags{ "Optimize", "FloatFast" }
	
	project "gmsv_cryptrandom"
		defines { "GMMODULE" }
		files { "src/**.*", "../include/**.*" }
		kind "SharedLib"
		