project "ZEngineAPI"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   targetname("zengine-api")

   filter "configurations:Debug"
      targetsuffix "-d"
   filter {}

   targetdir("%{prj.location}/../lib")
   objdir("%{prj.location}/../lib/obj/%{cfg.buildcfg}")

   files {
      "include/**.hpp",
      "include/**.inl",
      "src/**.cpp"
   }

   includedirs {
      "include"
   }

   pchsource "include/zepch.cpp"
   pchheader "zepch.hpp"

   filter "system:windows or linux"
      files { "include/zepch.cpp" }

   filter "system:windows"
      links {
         "version.lib"
      }
      systemversion "latest"

   filter "system:linux"
      links {
         "dl",
         "pthread"
      }

   filter "system:macosx"
      pchsource ""
      pchheader ""
