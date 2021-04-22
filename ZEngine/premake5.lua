project "ZEngine"
   kind "SharedLib"
   language "C++"
   cppdialect "C++17"

   targetname("zengine")
   
   filter "configurations:Debug"
      targetsuffix "-d"

   filter {}

   targetdir("%{prj.location}/lib")
   objdir("%{prj.location}/bin/%{cfg.buildcfg}")

   pchheader "zepch.hpp"
   pchsource "include/zepch.cpp"

   files {
      "src/**.cpp",
      "include/**.hpp",
      "include/**.inl",
      "include/zepch.cpp"
   }

   includedirs {
      "include"
   }

   filter "system:windows"
      systemversion "latest"
      links {
         "version.lib"
      }

   filter "system:linux"
      includedirs {
         "/usr/include",
         "/usr/local/include"
      }
      libdirs {
         "/usr/lib",
         "/usr/local/lib"
      }
      links {
         "dl",
         "pthread"
      }

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

   filter "configurations:Debug"
      defines "_DEBUG"
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines "NDEBUG"
      runtime "Release"
      optimize "On"
