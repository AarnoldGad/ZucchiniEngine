#include "zepch.hpp"

#include "zengine/Log/ConsoleColors.hpp"

namespace ze
{
   void ResetConsoleColor()
   {
      #if defined(ZE_PLATFORM_WINDOWS)
         HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(console, static_cast<uint8_t>(Color::White));
      #else
         std::cout << "\033[0m";
      #endif
   }

   void SetConsoleColor(Color color)
   {
      #if defined(_WIN32)
         HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(console, static_cast<uint8_t>(color));
      #else
         std::cout << "\033[" << (static_cast<uint8_t>(color) >> 4) << ";" << (static_cast<uint8_t>(color) & 0b1111) + 30 << "m";
      #endif
   }

   Color GetLevelColor(Logger::Level level) noexcept
   {
      switch (level)
      {
         case Logger::Level::Info:
            return Color::White;
         case Logger::Level::Debug:
            return Color::Aqua;
         case Logger::Level::Warn:
            return Color::Yellow;
         case Logger::Level::Error:
            return Color::Red;
         case Logger::Level::Critical:
            return Color::LightRed;
         default:
            return Color::White;
      }
   }
}
