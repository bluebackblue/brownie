-- premake5.lua

workspace "brownie"

configurations
{
	"Debug",
	"DeepDebug",
	"FullDebug",
	"Release"
}

platforms
{
	"Win32",
	"x64"
}

project "brownie"

do
	kind "WindowedApp"

	entrypoint "mainCRTStartup"

	language "C++"

	files
	{
		"**.inl",
		"**.h",
		"**.cpp"
	}

	filter "platforms:Win32"
	do
		libdirs
		{
			"../../sdk_32",
			"../../sdk",
		}

		includedirs
		{
			"./project_test",
			"../../sdk_32",
			"../../sdk",
		}
	end

	filter "platforms:x64"
	do
		libdirs
		{
			"../../sdk_64",
			"../../sdk",
		}

		includedirs
		{
			"./project_test",
			"../../sdk_64",
			"../../sdk",
		}
	end

	filter "action:vs*"
	do
		defines{
			"PLATFORM_VCWIN"
		}

		-- https://github.com/premake/premake-core/wiki/flags
		flags
		{
			"MultiProcessorCompile",
		}
	end

	filter "action:gmake"
	do
		defines
		{
			"PLATFORM_GNUCWIN"
		}

		-- https://github.com/premake/premake-core/wiki/cppdialect
		cppdialect "gnu++17"
	end

	filter "configurations:Debug"
	do
		defines { "ROM_DEVELOP" }
		symbols "On"
	end

	filter "configurations:DeepDebug"
	do
		defines { "ROM_DEEPDEBUG" }
		symbols "On"
	end

	filter "configurations:FullDebug"
	do
		defines { "ROM_FULLDEBUG" }
		symbols "On"
	end

	filter "configurations:Release"
	do
		defines { "ROM_MASTER" }
		optimize "On"
	end

	filter "platforms:Win32"
	do
		defines { "ROM_32BIT" }
	end

	filter "platforms:x64"
	do
		defines { "ROM_64BIT" }
	end

end

