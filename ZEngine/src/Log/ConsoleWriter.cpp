#include "zepch.hpp"

#include "zengine/Log/ConsoleWriter.hpp"

#include "zengine/Common/Console.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/chrono.h>

#include <string_view>

namespace ze
{
   ConsoleWriter::ConsoleWriter()
      : m_atLineStart(true) {}

   void ConsoleWriter::write(std::string_view name, Date date, Logger::Level level, std::string_view message)
   {
      Console::SetColor(Logger::GetLevelColor(level));
      
      if (m_atLineStart)
      {
         fmt::print(std::cout, "[{1:%H:%M:%S}] [{2}] <{0}> ", name, date.getTm(), Logger::LevelToString(level));
         m_atLineStart = false;
      }

      fmt::print(std::cout, "{}", message);

      Console::ResetColor();
   }
   
   void ConsoleWriter::flush()
   {
      std::cout.flush();
   }

   void ConsoleWriter::endLine()
   {
      if (m_atLineStart) return;

      std::cout.put('\n');
      std::cout.flush();
      m_atLineStart = true;
   }
}

