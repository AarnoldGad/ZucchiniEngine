#include "zepch.hpp"

#include "zengine/Log/DebugFileWriter.hpp"
#include "zengine/Log/ConsoleColors.hpp"
#include "zengine/Time/Date.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   DebugFileWriter::DebugFileWriter(std::string_view path, std::ostream& console)
      : FileWriter(path), m_lineStart(true), m_console(console) {}

   void DebugFileWriter::write(std::string_view name, Level level, std::string_view line)
   {
      FileWriter::write(name, level, line);

      ze::SetConsoleColor(ze::GetLevelColor(level));

      if (m_lineStart)
      {
         Date date = Date::CurrentDate();
         std::tm tm = date.getTm();
         m_console << "[" << std::put_time(&tm, "%H:%M:%S") << "] [" << LevelToString(level) << "] <" << name << "> ";
         m_lineStart = false;
      }

      m_console.write(line.data(), line.size());

      ze::ResetConsoleColor();
   }

   void DebugFileWriter::flush()
   {
      FileWriter::flush();
      m_console.flush();

      m_lineStart = true;
   }
}
