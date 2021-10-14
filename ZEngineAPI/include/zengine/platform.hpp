// Platform detection
#if defined(_WIN32) // Windows

   //#if defined(_WIN64)
      #define ZE_PLATFORM_WINDOWS
   //#else
      //#error "32-bit platforms not supported !"
   //#endif

   #ifdef _MSC_VER
      #pragma warning(disable: 4251)
   #endif

#elif defined(__ANDROID__) // Android

   #define ZE_PLATFORM_ANDROID
   #error "Android platform not supported !"

#elif defined(__linux__) // Linux

   #if defined(__x86_64__) || defined(__aarch64__)
      #define ZE_PLATFORM_LINUX
   #else
      #error "32-bit platforms not supported !"
   #endif

#elif defined(__APPLE__) || defined(__MACH__) // MacOS

   #define ZE_PLATFORM_APPLE

#else

   #error "Unsupported platform or architecture !"

#endif // Platform detection

// DLL/SO specifiers
// ZE_API is for the ZEngine API build as static library
// ZE_APP_API is for the app loaded by the engine as a dynamic library
#if __GNUC__ >= 4 || defined(__clang__) // GNU GCC __attribute__

   #define ZE_API __attribute__ ((__visibility__("default")))
   #define ZE_APP_API __attribute__ ((__visibility__("default")))

#elif defined(_WIN32)

   #if defined(_WINDLL)
      #define ZE_API
      #define ZE_APP_API __declspec(dllexport)
   #else
      #define ZE_API
      #define ZE_APP_API __declspec(dllimport)
   #endif

#else // idk

   #define ZE_API
   #define ZE_APP_API

#endif // DLL/SO specifiers
