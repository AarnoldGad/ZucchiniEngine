#ifndef ZE_BUILD
#define ZE_BUILD

#include <cstdint>

// Platform detection
#if defined(_WIN32) // Windows

   #if defined(_WIN64)
      #define ZE_BUILD_WINDOWS
   #else
      #error "32-bit platform not supported !"
   #endif

   #ifdef _MSC_VER
      #pragma warning(disable: 4251)
   #endif

#elif defined(__ANDROID__) // Android

      #define ZE_BUILD_ANDROID
      #error "Android platform not supported !"

#elif defined(__linux__) // Linux

   #if __UINTPTR_MAX__ == 0xffffffffffffffff
      #define ZE_BUILD_LINUX
   #else
      #error "32-bit platform not supported !"
   #endif

#elif defined(__APPLE__) || defined(__MACH__) // MacOS

   #define ZE_BUILD_APPLE
   #error "MacOS not supported !"

#else

   #error "Unsupported platform or architecture !"

#endif

// DLL/SO attributes
#if defined(ZE_BUILD_WINDOWS) // Windows __declspec

   #if defined(_WINDLL)
      #define ZE_API __declspec(dllexport)
   #else
      #define ZE_API __declspec(dllimport)
   #endif

#elif __GNUC__ >= 4 // GNU GCC

   #define ZE_API __attribute__ ((__visibility__("default")))

#else // idk

   #define ZE_API

#endif

#endif // ZE_BUIL
