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

#include "zengine/defines.hpp"

#include "zengine/Common/Console.hpp"

#include <fmt/format.h>

#include <initializer_list>
#include <string_view>
#include <type_traits>
#include <vector>
#include <initializer_list>

#define MAX_LOGLINE_LENGTH 150

namespace ze
{
   class Writer;

   class ZE_API Logger
   {
   public:
      enum class Level : uint8_t
      {
         Info     = FLAG(0),
         Debug    = FLAG(1),
         Warning  = FLAG(2),
         Error    = FLAG(3),
         Critical = FLAG(4),
      };

      static char const* LevelToString(Level level) noexcept;
      static Console::Color GetLevelColor(Logger::Level level) noexcept;

      template<typename Message>
      Logger& log(Message message);

      template<typename Message>
      Logger& log(Level level, Message message);

      template<typename... Args>
      Logger& logFormatted(fmt::format_string<Args...> fmt, Args&&... args);

      template<typename... Args>
      Logger& logFormatted(Level level, fmt::format_string<Args...> fmt, Args&&... args);

      template<typename... Args>
      Logger& logLine(fmt::format_string<Args...> fmt, Args&&... args);
      
      template<typename... Args>
      Logger& logLine(Level level, fmt::format_string<Args...> fmt, Args&&... args);

      template<typename Message>
      Logger& operator<<(Message message);
      
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

      Logger& stacktrace();
      static Logger& stacktrace(Logger& logger);

      Logger& endLine();
      static Logger& endLine(Logger& logger);

      void setName(std::string const& name);
      std::string getName() const noexcept;

      void addWriter(Writer* writer);
      void removeWriter(Writer* writer);
      void removeWriters();

      void setLogMask(uint8_t mask) noexcept;
      uint8_t getLogMask() const noexcept;

      explicit Logger(std::string const& name = "UNDEFINED", uint8_t logMask = 0xFF);
      Logger(std::string const& name, Writer* writer, uint8_t logMask = 0xFF);
      Logger(std::string const& name, std::initializer_list<Writer*> writers, uint8_t logMask = 0xFF);

   private:
      bool canLog() const noexcept;

      template<typename... Args>
      void write(fmt::format_string<Args...> fmt, Args&&... args);
      void write(std::string_view line);

      void setLogLevel(Level level) noexcept;
      Level getLogLevel() const noexcept;

      Logger& startNewLineAs(Level level);

      std::string m_name;
      std::vector<Writer*> m_writers;

      uint8_t m_logMask; //<- Members of Level enum to be OR-ed together
      Level m_logLevel;
   };
}

#include "Logger.inl"

#endif // ZE_LOGGER_HPP
