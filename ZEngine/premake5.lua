project "ZEngine"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   targetname("zengine")

   filter "configurations:Debug"
      targetsuffix "-d"
   filter {}

   targetdir("%{prj.location}/../lib")
   objdir("%{prj.location}/obj/%{cfg.buildcfg}")

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

   filter "system:windows"
      kind "StaticLib"
      files { "include/zepch.cpp" }
      links {
         "version.lib"
      }
      systemversion "latest"

   filter "system:linux"
      kind "SharedLib"
      links {
         "dl",
         "pthread"
      }

   filter "system:macosx"
      kind "SharedLib"
      pchsource ""
      pchheader ""

   filter { "action:gmake*", "toolset:gcc" }
      buildoptions {
         "-Wall", "-Wextra", "-Wold-style-cast", "-Woverloaded-virtual", "-Wfloat-equal", "-Wwrite-strings",
         "-Wpointer-arith", "-Wcast-qual", "-Wcast-align", "-Wconversion", "-Wshadow", "-Wredundant-decls",
         "-Wdouble-promotion", "-Winit-self", "-Wswitch-default", "-Wswitch-enum", "-Wundef", "-Wlogical-op", "-Winline",
         "-fPIC", "-m64", "-fexceptions", "-pedantic"
      }
      linkoptions {
         "-fPIC", "-shared", "-lc", "-m64"
      }
