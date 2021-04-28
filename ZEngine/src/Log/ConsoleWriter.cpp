#include "zepch.hpp"

#include "zengine/Log/ConsoleWriter.hpp"
#include "zengine/Log/ConsoleColors.hpp"
#include "zengine/Time/Date.hpp"

namespace ze
{
   ConsoleWriter::ConsoleWriter(std::ostream& console)
      : m_console(console), m_lineStart(true) {}

   void ConsoleWriter::write(std::string_view name, Level level, std::string_view line)
   {
      ze::SetConsoleColor(ze::GetLevelColor(level));

      if (m_lineStart)
      {
         Date date = Date::CurrentDate();
         m_console << "[" << std::put_time(&date.getTm(), "%H:%M:%S") << "] [" << LevelToString(level) << "] <" << name << "> ";
         m_lineStart = false;
      }

      m_console.write(line.data(), line.size());

      ze::ResetConsoleColor();
   }

   void ConsoleWriter::flush()
   {
      m_console.flush();
      m_lineStart = true;
   }
}