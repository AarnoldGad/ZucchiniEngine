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
#ifndef ZE_LOGGER_HPP
#define ZE_LOGGER_HPP

#include "zapi/defines.hpp"

#include <iostream>
#include <string>
#include <charconv>
#include <sstream>

#ifdef ZE_PLATFORM_WINDOWS
   #include <Windows.h>
#endif

namespace ze
{
   class Writer;

   class ZE_API Logger
   {
   public:
      enum Level : uint8_t
      {
         Info = FLAG(0),
         Debug = FLAG(1),
         Warn = FLAG(2),
         Error = FLAG(3),
         Critical = FLAG(4)
      };
      
      static char const* LevelToString(Level level) noexcept;

      template<typename Message>
      void log(Message&& message);

      template<typename Message, typename std::enable_if_t<std::is_arithmetic_v<Message>, int> = 0>
      void log(Level logLevel, Message message);

      template<typename Message, typename std::enable_if_t<std::is_convertible_v<Message, std::string_view>, int> = 0>
      void log(Level logLevel, Message message);

      template<typename... Args>
      void logLine(std::string_view format, Args&&... args);

      template<typename... Args>
      void logLine(Level logLevel, std::string_view format, Args&&... args);

      template<typename Message>
      Logger& operator<<(Message&& message);
      //Logger& operator<<(std::ostream& (*manip)(std::ostream&));
      Logger& operator<<(Logger& (*manip)(Logger&));

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

      Logger& stacktrace();
      static Logger& stacktrace(Logger& logger);

      void setName(std::string const& name);
      std::string getName() const noexcept;

      void setWriter(Writer* writer) noexcept;
      Writer* getWriter() noexcept;

      void setLogMask(uint8_t mask) noexcept;
      uint8_t getLogMask() const noexcept;

      bool canLog() const noexcept;

      explicit Logger(std::string const& name = "UNDEFINED", Writer* = nullptr, uint8_t logMask = 0xFF);

   private:
      template<typename... Args>
      void write(std::string_view format, Args&&... args);

      void write(std::string_view message);

      void setLogLevel(Level logLevel) noexcept;
      Level getLogLevel() const noexcept;

      Logger& startNewLineAs(Level logLevel);

      std::string m_name;
      Writer* m_writer;

      uint8_t m_logMask; //<- Members of Level enum to be OR-ed together
      Level m_logLevel;
      bool m_lineStart;
   };
}

#include "Logger.inl"

#endif // ZE_LOGGER_HPP
