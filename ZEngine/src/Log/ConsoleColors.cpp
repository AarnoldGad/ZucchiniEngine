#include "zepch.hpp"

#include "zengine/Log/ConsoleColors.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   void ResetConsoleColor()
   {
      #if defined(ZE_PLATFORM_WINDOWS)
         HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(console, static_cast<uint8_t>(Color::White));
      #elif defined(ZE_PLATFORM_LINUX)
         std::cout << "\033[0m";
      #endif
   }

   void SetConsoleColor(Color color)
   {
      #if defined(ZE_PLATFORM_WINDOWS)
         HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(console, static_cast<uint8_t>(color));
      #elif defined(ZE_PLATFORM_LINUX)
         std::cout << "\033[" << (static_cast<uint8_t>(color) >> 4) << ";" << (static_cast<uint8_t>(color) & 0b1111) + 30 << "m";
      #endif
   }

   Color GetLevelColor(Level level) noexcept
   {
      switch (level)
      {
         case Level::Info:
            return Color::White;
         case Level::Debug:
            return Color::Aqua;
         case Level::Warn:
            return Color::Yellow;
         case Level::Error:
            return Color::Red;
         case Level::Critical:
            return Color::LightRed;
         default:
            return Color::White;
      }
   }
}