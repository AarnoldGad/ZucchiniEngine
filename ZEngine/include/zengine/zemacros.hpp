#ifndef ZE_MACROS_HPP
#define ZE_MACROS_HPP

#include "zeplatform.hpp"

#include <cstring>
#include <iostream>

#define ZE_VERSION_MAJOR 0
#define ZE_VERSION_MINOR 9
#define ZE_VERSION_REV 0
#define ZE_VERSION_SPEC "pre"
#define ZE_VERSION_MONTH 7
#define ZE_VERSION_DAY 15
#define ZE_VERSION_YEAR 21 

//#define ZE_DEBUG_LOG_MEMORYALLOC

#define FLAG(shift) 1 << shift
#define MACRO_TO_STRING(x) TO_STRING(x)
#define TO_STRING(str) #str

#ifdef ZE_PLATFORM_WINDOWS
   #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
   #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#if defined(_DEBUG)
   template<typename... Args>
   inline void LOG_TRACE(Args... args)
   {
      (std::cout << ... << args) << std::endl;
   }
#else
   #define LOG_TRACE(...)
#endif

#define ZE_LOG_INFO(...)     ::ze::Core::UseCoreLogger().logLine(::ze::Level::Info    , __VA_ARGS__)
#define ZE_LOG_DEBUG(...)    ::ze::Core::UseCoreLogger().logLine(::ze::Level::Debug   , __VA_ARGS__)
#define ZE_LOG_WARN(...)     ::ze::Core::UseCoreLogger().logLine(::ze::Level::Warn    , __VA_ARGS__)
#define ZE_LOG_ERROR(...)    ::ze::Core::UseCoreLogger().logLine(::ze::Level::Error   , __VA_ARGS__)
#define ZE_LOG_CRITICAL(...) ::ze::Core::UseCoreLogger().logLine(::ze::Level::Critical, __VA_ARGS__)

#define APP_LOG_INFO(...)     if (::ze::Core::GetApplication()) ::ze::Core::GetApplication()->useAppLogger().logLine(::ze::Level::Info    , __VA_ARGS__)
#define APP_LOG_DEBUG(...)    if (::ze::Core::GetApplication()) ::ze::Core::GetApplication()->useAppLogger().logLine(::ze::Level::Debug   , __VA_ARGS__)
#define APP_LOG_WARN(...)     if (::ze::Core::GetApplication()) ::ze::Core::GetApplication()->useAppLogger().logLine(::ze::Level::Warn    , __VA_ARGS__)
#define APP_LOG_ERROR(...)    if (::ze::Core::GetApplication()) ::ze::Core::GetApplication()->useAppLogger().logLine(::ze::Level::Error   , __VA_ARGS__)
#define APP_LOG_CRITICAL(...) if (::ze::Core::GetApplication()) ::ze::Core::GetApplication()->useAppLogger().logLine(::ze::Level::Critical, __VA_ARGS__)

#include "zengine/Debug/Assert.hpp"
#include "zengine/Debug/Tee.hpp"

#endif // ZE_MACROS_HPP
