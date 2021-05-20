#ifndef ZE_MACROS_HPP
#define ZE_MACROS_HPP

#include "zeplatform.hpp"

#include <cstring>
#include <iostream>

#define ZE_VERSION_MAJOR 0
#define ZE_VERSION_MINOR 21
#define ZE_VERSION_PATCH 4
#define ZE_VERSION_REV 27

#define FLAG(shift) 1 << shift
#define MACRO_TO_STRING(x) TO_STRING(x)
#define TO_STRING(str) #str

#ifdef ZE_PLATFORM_WINDOWS
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

#define ZE_LOG_INFO(format, ...)     ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Level::Info     , format, __VA_ARGS__)
#define ZE_LOG_DEBUG(format, ...)    ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Level::Debug    , format, __VA_ARGS__)
#define ZE_LOG_WARN(format, ...)     ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Level::Warn     , format, __VA_ARGS__)
#define ZE_LOG_ERROR(format, ...)    ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Level::Error    , format, __VA_ARGS__)
#define ZE_LOG_CRITICAL(format, ...) ::ze::Core::GetApplication().useCoreLogger().logLine(::ze::Level::Critical , format, __VA_ARGS__)

#define APP_LOG_INFO(format, ...)     ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Level::Info     , format, __VA_ARGS__)
#define APP_LOG_DEBUG(format, ...)    ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Level::Debug    , format, __VA_ARGS__)
#define APP_LOG_WARN(format, ...)     ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Level::Warn     , format, __VA_ARGS__)
#define APP_LOG_ERROR(format, ...)    ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Level::Error    , format, __VA_ARGS__)
#define APP_LOG_CRITICAL(format, ...) ::ze::Core::GetApplication().useClientLogger().logLine(::ze::Level::Critical , format, __VA_ARGS__)

#include "zengine/Debug/Assert.hpp"
#include "zengine/Debug/Tee.hpp"

#endif // ZE_MACROS_HPP
