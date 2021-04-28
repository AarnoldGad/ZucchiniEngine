// Platform detection
#if defined(_WIN32) // Windows

   #if defined(_WIN64)
      #define ZE_PLATFORM_WINDOWS
   #else
      #error "32-bit platforms not supported !"
   #endif

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
   #error "MacOS not supported !"

#else

   #error "Unsupported platform or architecture !"

#endif // Platform detection

// DLL/SO specifiers
#if defined(ZE_PLATFORM_WINDOWS) // Windows __declspec

   #if defined(_WINDLL)
      #define ZE_API __declspec(dllexport)
   #else
      #define ZE_API __declspec(dllimport)
   #endif

#elif __GNUC__ >= 4 // GNU GCC __attribute__

   #define ZE_API __attribute__ ((__visibility__("default")))

#else // idk

   #define ZE_API

#endif // DLL/SO specifiers