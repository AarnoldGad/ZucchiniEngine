#include "zepch.hpp"

#include "zengine/Log/ConsoleWriter.hpp"
#include "zengine/Log/ConsoleColors.hpp"
#include "zengine/Time/Date.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   ConsoleWriter::ConsoleWriter(std::ostream& console)
      : m_console(console), m_lineStart(true) {}

   void ConsoleWriter::write(std::string_view name, Level level, std::string_view line)
   {
      ze::SetConsoleColor(ze::GetLevelColor(level));

      if (isAtLineBegin())
      {
         Date date = Date::CurrentDate();
         std::tm tm = date.getTm();
         m_console << "[" << std::put_time(&tm, "%H:%M:%S") << "] [" << LevelToString(level) << "] <" << name << "> ";
         m_lineStart = false;
      }

      m_console.write(line.data(), line.size());

      ze::ResetConsoleColor();
   }

   void ConsoleWriter::flush()
   {
      m_console.flush();
   }

   void ConsoleWriter::newLine()
   {
      m_console.put('\n');
      m_lineStart = true;
   }
}
