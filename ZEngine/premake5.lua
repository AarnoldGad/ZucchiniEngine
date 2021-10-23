project "ZEngine"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   targetdir("%{prj.location}/../bin")
   objdir("%{prj.location}/obj/%{cfg.buildcfg}")

   files {
      "src/**.cpp",
      "include/**.hpp",
      "include/**.inl"
   }

   includedirs {
      "include"
   }

   links {
      "ZEngineAPI"
   }

   filter "system:windows"
      systemversion "latest"

   filter "system:linux"
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
