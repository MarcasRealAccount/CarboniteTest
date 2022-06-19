require("Premake/Common")

require("Premake/ThirdParty/entt")
require("Premake/ThirdParty/glfw")
require("Premake/ThirdParty/glad")
require("Premake/ThirdParty/glm")
require("Premake/ThirdParty/stb")
require("Premake/ThirdParty/imgui")
require("Premake/ThirdParty/spdlog")
require("Premake/ThirdParty/vulkan")
require("Premake/ThirdParty/vma")

workspace("Carbonite")
	common:setConfigsAndPlatforms()
	common:addCoreDefines()

	cppdialect("C++20")
	rtti("Off")
	exceptionhandling("On")
	flags("MultiProcessorCompile")

	startproject("Carbonite")

	group("Dependencies")
	project("EnTT")
		location("ThirdParty/EnTT/")
		warnings("Off")
		libs.entt:setup()
		location("ThirdParty/")

	project("GLFW")
		location("ThirdParty/GLFW/")
		warnings("Off")
		libs.glfw:setup()
		location("ThirdParty/")

	project("VMA")
		location("ThirdParty/VMA/")
		warnings("Off")
		libs.vma:setup()
		location("ThirdParty/")

	project("SpdLog")
		location("ThirdParty/SpdLog/")
		warnings("Off")
		libs.spdlog:setup()
		location("ThirdParty/")

	project("GLM")
		location("ThirdParty/GLM/")
		warnings("Off")
		libs.glm:setup()
		location("ThirdParty/")

	project("glad")
		location("ThirdParty/glad/")
		warnings("Off")
		libs.glad:setup()
		location("ThirdParty/")

	project("STB")
		location("ThirdParty/STB/")
		warnings("Off")
		libs.stb:setup()
		location("ThirdParty/")

	project("ImGUI")
		location("ThirdParty/ImGUI/")
		warnings("Off")
		libs.imgui:setup()
		location("ThirdParty/")

	project("Vulkan")
		location("ThirdParty/Vulkan/")
		warnings("Off")
		libs.vulkan:setup()
		location("ThirdParty/")

	group("Apps")
	project("Carbonite")
		location("Carbonite/")
		warnings("Extra")

		common:outDirs()
		common:debugDir()

		filter("configurations:Debug")
			kind("ConsoleApp")

		filter("configurations:not Debug")
			kind("WindowedApp")

		filter({})

		common:addPCH("%{prj.location}/Src/PCH.cpp", "%{prj.location}/Src/PCH.h")

		includedirs({ "%{prj.location}/Src/" })
		files({ "%{prj.location}/Src/**" })
		removefiles({ "*.DS_Store" })

		libs.entt:setupDep()
		libs.glfw:setupDep()
		libs.glad:setupDep()
		libs.glm:setupDep()
		libs.stb:setupDep()
		libs.imgui:setupDep()
		libs.spdlog:setupDep()
		libs.vulkan:setupDep()
		libs.vma:setupDep()

		common:addActions()
