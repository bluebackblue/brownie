-- premake5.lua

workspace "brownie"

configurations
{
	"Debug",
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

	flags
	{
		"WinMain"
	}

	language "C++"

	files{
		"**.inl",
		"**.h",
		"**.cpp"
	}

	includedirs{
		"./project_test",
		"../../sdk"
	}

	libdirs{
		"../../sdk"
	}

	filter "action:vs*"
	do
		-- buildoptions
		-- {
		-- 	"/MP",
		-- }

		defines{
			"PLATFORM_VCWIN"
		}
	end

	filter "configurations:Debug"
	do
		defines { "ROM_DEVELOP" }
		flags { "Symbols" }
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

