project "ZEngine"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "on"

   targetname("zengine")

   filter "configurations:Debug"
      targetsuffix "-d"
   filter {}

   targetdir("%{prj.location}/../bin")
   objdir("%{prj.location}/../bin/obj/%{cfg.buildcfg}")

   files {
      "src/**.cpp",
      "include/**.hpp",
      "include/**.inl"
   }

   includedirs {
      "include"
   }

   links {
      "ZAPI"
   }

   filter "system:windows"
      systemversion "latest"

   filter "system:linux"
      links {
         "dl",
         "pthread"
      }
