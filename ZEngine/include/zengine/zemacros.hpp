#ifndef ZE_MACROS
#define ZE_MACROS

#include "zebuild.hpp"

#define ZE_VERSION_MAJOR 0
#define ZE_VERSION_MINOR 21
#define ZE_VERSION_PATCH 4
#define ZE_VERSION_REV 11

#define FLAG(shift) 1 << shift
#define MACRO_TO_STRING(x) TO_STRING(x)
#define TO_STRING(str) #str

#include <cstring>
#include <iostream>

#ifdef ZE_BUILD_WINDOWS
   #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
   #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#if defined(_DEBUG)
   #define ZE_DEBUG
#elif defined(NDEBUG)
   #define ZE_NDEBUG
#endif

#if defined(ZE_DEBUG)
   template<typename... Args>
   inline void LOG_TRACE(Args... args)
   {
      (std::cout << ... << args) << std::endl;
   }
#else
   #define LOG_TRACE(...)
#endif

#define ZE_LOG_INFO(...)     ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Logger::Level::INFO    , __VA_ARGS__)
#define ZE_LOG_DEBUG(...)    ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Logger::Level::DEBUG   , __VA_ARGS__)
#define ZE_LOG_WARN(...)     ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Logger::Level::WARN    , __VA_ARGS__)
#define ZE_LOG_ERROR(...)    ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Logger::Level::ERROR   , __VA_ARGS__)
#define ZE_LOG_CRITICAL(...) ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Logger::Level::CRITICAL, __VA_ARGS__)

#define APP_LOG_INFO(...)     ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Logger::Level::INFO    , __VA_ARGS__)
#define APP_LOG_DEBUG(...)    ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Logger::Level::DEBUG   , __VA_ARGS__)
#define APP_LOG_WARN(...)     ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Logger::Level::WARN    , __VA_ARGS__)
#define APP_LOG_ERROR(...)    ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Logger::Level::ERROR   , __VA_ARGS__)
#define APP_LOG_CRITICAL(...) ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Logger::Level::CRITICAL, __VA_ARGS__)

#include "zengine/Debug/Assert.hpp"
#include "zengine/Debug/Tee.hpp"

#endif // ZE_MACROS
