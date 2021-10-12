/**
 * ConsoleColors.hpp
 * 27 Apr 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_CONSOLECOLORS_HPP
#define ZE_CONSOLECOLORS_HPP

#include "zapi/defines.hpp"

#include "zapi/Log/Logger.hpp"

namespace ze
{
   #if defined(_WIN32)
      enum class Color : uint8_t
      {
         Black = 0, Blue, Green, Aqua,
         Red, Purple, Yellow, White,
         Gray, LightBlue, LightGreen, LightAqua,
         LightRed, LightPurple, LightYellow, BrightWhite
      };
   #else
      enum class Color : uint8_t // Actual ANSI colors are limited due to compatibility of interface between platforms
      {
         Black = 0, Red = 0b001, Green = 0b010, Yellow = 0b011, Blue = 0b100, LightPurple = 0b101, LightAqua = 0b110, White = 0b111,
         LightRed = 0b10001, LightGreen = 0b10010, LightYellow = 0b10011, LightBlue = 0b10100, Purple = 0b10101, Aqua = 0b10110, Gray = 0b100000, BrightWhite = 0b100111
      };
   #endif

   ZE_API void ResetConsoleColor();
   ZE_API void SetConsoleColor(Color color);
   ZE_API Color GetLevelColor(Logger::Level level) noexcept;
}

#endif // ZE_CONSOLECOLORS_HPP
