#include "zepch.hpp"

#include "zengine/Log/ConsoleWriter.hpp"
#include "zengine/Log/ConsoleColors.hpp"
#include "zengine/Time/Date.hpp"

#include "zengine/Common/Console.hpp"


namespace ze
{
   ConsoleWriter::ConsoleWriter()
      : m_lineStart(true) {}

   void ConsoleWriter::write(std::string_view name, Logger::Level level, std::string_view line)
   {
      if (isAtLineBegin())
      Console::SetColor(Logger::GetLevelColor(level));
      
      {
         Date date = Date::CurrentDate();
         std::tm tm = date.getTm();
         std::cout << "[" << std::put_time(&tm, "%H:%M:%S") << "] [" << Logger::LevelToString(level) << "] <" << name << "> ";
         m_lineStart = false;
      }

      std::cout.write(line.data(), static_cast<std::streamsize>(line.size()));

      Console::ResetColor();
   }

   void ConsoleWriter::flush()
   {
      std::cout.flush();
   }

   void ConsoleWriter::newLine()
   {
      std::cout.put('\n');
      m_lineStart = true;
   }
}
