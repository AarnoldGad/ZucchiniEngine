/**
 * Logger.hpp
 * 1 Dec 2020
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
#ifndef ZE_LOGGER
#define ZE_LOGGER

#include "zengine/zemacros.hpp"

#include <iostream>
#include <string>

#ifdef ZE_BUILD_WINDOWS
   #include <Windows.h>
#endif

#define LOGGERNAME_MAXSIZE 15

namespace ze
{
   // TODO Print thread name / Print stacktrace / Check output stream validity
   class ZE_API Logger
   {
   public:
      #if defined(ZE_BUILD_WINDOWS)
         enum class TextColor : unsigned short
         {
            Black = 0, Blue,        Green,       Aqua,
            Red,       Purple,      Yellow,      White,
            Gray,      LightBlue,   LightGreen,  LightAqua,
            LightRed,  LightPurple, LightYellow, BrightWhite
         };
      #elif defined(ZE_BUILD_LINUX)
         enum class TextColor : unsigned short // Actual ANSI colors are limited due to compatibility of interface between platforms
         {
            Black = 0, Red = 0b001, Green = 0b010, Yellow = 0b011, Blue = 0b100, LightPurple = 0b101, LightAqua = 0b110, White = 0b111,
            LightRed = 0b10001, LightGreen = 0b10010, LightYellow = 0b10011, LightBlue = 0b10100, Purple = 0b10101, Aqua = 0b10110, Gray = 0b100000, BrightWhite = 0b100111
         };
      #endif

      enum Level
      {
         INFO     = FLAG(0),
         DEBUG    = FLAG(1),
         WARN     = FLAG(2),
         ERR    = FLAG(3),
         CRITICAL = FLAG(4)
      };

   // Member functions
      template<typename Message>
      void log(Level logLevel, Message const& message);

      template<typename... Messages>
      void logLine(Level logLevel, Messages&&... messages);

      template<typename... Args>
      void logFormatedLine(Level logLevel, std::string_view unformattedLine, Args&&... args);

      std::string getName() const noexcept;

      void setOutput(std::ostream& output);
      void setOutput(std::streambuf* output);
      std::ostream& getOutput() noexcept;

      void setLogToConsole(bool logToConsole) noexcept;

      void setLogMask(unsigned int mask) noexcept;
      unsigned int getLogMask() const noexcept;

      bool canLog() const noexcept;
      bool isConsole() const noexcept;
      bool canLogToConsole() const noexcept;

   // Operators
      template<typename Message>
      Logger& operator<<(Message const& message);
      Logger& operator<<(std::ostream& (*manip)(std::ostream&));
      Logger& operator<<(Logger& (*manip)(Logger&));

   // Manipulators
      Logger& info();
      static Logger& info(Logger& logger);

      Logger& debug();
      static Logger& debug(Logger& logger);

      Logger& warn();
      static Logger& warn(Logger& logger);

      Logger& error();
      static Logger& error(Logger& logger);

      Logger& critical();
      static Logger& critical(Logger& logger);

      Logger& newLine();
      static Logger& newLine(Logger& logger);

      // TODO Stacktrace
      //Logger& stacktrace();
      //static Logger& stacktrace(Logger& logger);

      // Constructors/Destructor
      Logger(std::string_view name, std::ostream& output, bool outputToConsole = false, unsigned int logMask = 0xFF);
      explicit Logger(std::string_view name = "UNDEFINED", std::streambuf* = nullptr, bool outputToConsole = false, unsigned int logMask = 0xFF);
      ~Logger();

   private:
      void printLineDetails();

      template<unsigned int N = 1, typename Head, typename... Tail>
      std::string formatLine(std::string_view unformattedLine, Head const& head, Tail&&... tail);
      template<unsigned int N = 1, typename Arg>
      std::string formatLine(std::string_view unformattedLine, Arg const& arg);

      void setConsoleColor() const;
      void resetConsoleColor() const;
      TextColor getCorrespondingTextColor() const noexcept;

      void setLogLevel(Level logLevel) noexcept;
      Logger& startNewLineAs(Level logLevel);

      template<typename Head, typename... Tail>
      void write(Head const& head, Tail&&... tail);

      template<typename Message>
      void write(Message const& message);

      template<typename Message>
      void logToConsole(Message const& message);

      static char const* levelToString(Level logLevel) noexcept;

      char m_name[LOGGERNAME_MAXSIZE + 1];
      std::ostream m_output;
      bool m_outputToConsole;
      unsigned int m_logMask; // Members of Level enum to be ORed together
      bool m_lineStart;
      Level m_logLevel;
   };
}

#include "Logger.inl"

#endif // ZE_LOGGER
