#include "zepch.hpp"

#include "zengine/Log/LogLevels.hpp"

namespace ze
{
   char const* LevelToString(Level level) noexcept
   {
      switch (level)
      {
         case Level::Info:
            return "Info";
         case Level::Debug:
            return "Debug";
         case Level::Warn:
            return "Warn";
         case Level::Error:
            return "Error";
         case Level::Critical:
            return "Critical";
         default:
            return "None";
      }
   }
}