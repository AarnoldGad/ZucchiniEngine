#ifndef ZE_DEFINES_HPP
#define ZE_DEFINES_HPP

#include "zeconfig.hpp"
#include "platform.hpp"

#include <cstring>

#define FLAG(shift) (1 << shift)
#define MACRO_TO_STRING(x) TO_STRING(x)
#define TO_STRING(str) #str

#ifdef ZE_PLATFORM_WINDOWS
   #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
   #define __FILENAME__ (strrchr(__FILE__, '/' ) ? strrchr(__FILE__, '/' ) + 1 : __FILE__)
#endif

typedef struct
{
   char const* file;
   unsigned int line;
   char const* function;
} SourceLocation;

#define CURRENT_SOURCE_LOCATION SourceLocation{__FILENAME__, static_cast<unsigned int>(__LINE__), __func__ }

#define ZE_LOG_INFO(...)     ::ze::Core::UseCoreLogger().info().logLine(__VA_ARGS__)
#define ZE_LOG_DEBUG(...)    ::ze::Core::UseCoreLogger().debug().logLine(__VA_ARGS__)
#define ZE_LOG_WARN(...)     ::ze::Core::UseCoreLogger().warn().logLine(__VA_ARGS__)
#define ZE_LOG_ERROR(...)    ::ze::Core::UseCoreLogger().error().logLine(__VA_ARGS__)
#define ZE_LOG_CRITICAL(...) ::ze::Core::UseCoreLogger().critical().logLine(__VA_ARGS__)

#define APP_LOG_INFO(...)     ::ze::Core::UseAppLogger().info().logLine(__VA_ARGS__)
#define APP_LOG_DEBUG(...)    ::ze::Core::UseAppLogger().debug().logLine(__VA_ARGS__)
#define APP_LOG_WARN(...)     ::ze::Core::UseAppLogger().warn().logLine(__VA_ARGS__)
#define APP_LOG_ERROR(...)    ::ze::Core::UseAppLogger().error().logLine(__VA_ARGS__)
#define APP_LOG_CRITICAL(...) ::ze::Core::UseAppLogger().critical().logLine(__VA_ARGS__)

#include "zengine/Debug/Assert.hpp"

#endif // ZE_DEFINES_HPP
