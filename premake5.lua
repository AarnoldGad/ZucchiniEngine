workspace "ZucchiniEngine"
   architecture "x86_64"
   configurations { "Debug", "Release" }

   sysincludedirs {
      "ZEngineAPI/include"
   }

   syslibdirs {
      "lib"
   }

   filter "system:linux or macosx"
      sysincludedirs {
         "/usr/include",
         "/usr/local/include"
      }
      syslibdirs {
         "/usr/lib",
         "/usr/local/lib"
      }

   filter "configurations:Debug"
      defines "_DEBUG"
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines "NDEBUG"
      runtime "Release"
      optimize "on"

include "ZEngine"
include "ZEngineAPI"
