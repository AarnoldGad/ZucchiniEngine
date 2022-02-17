#include "zepch.hpp"

#include "zengine/Common/Console.hpp"

namespace ze
{
   void Console::SetColor(Color color)
   {
      #if defined(_WIN32)
         HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(console, static_cast<uint8_t>(color));
      #else
         std::cout << "\033[" << (static_cast<uint8_t>(color) >> 4) << ";" << (static_cast<uint8_t>(color) & 0b1111) + 30 << "m";
      #endif
   }

   void Console::ResetColor()
   {
      #if defined(_WIN32)
         HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(console, static_cast<uint8_t>(Color::White));
      #else
         std::cout << "\033[0m";
      #endif
   }
}

